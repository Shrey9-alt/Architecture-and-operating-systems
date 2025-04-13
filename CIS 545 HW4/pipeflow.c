#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define RECORD_SIZE 3       // Format: 'C'/'D' + digit + null terminator
#define RECORD_COUNT 10     // Number of records to generate
#define LOG_LIMIT 30        // Total log messages expected
#define LOG_MSG_SIZE 100    // Buffer size for log messages
#define TIMESTAMP_SIZE 20   // Buffer size for timestamp

typedef struct {
    int a_to_b[2];  
    int b_to_c[2];   
    int b_to_d[2];   
    int log_pipe[2]; 
} Pipeline;

void generate_timestamp(char *buffer) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, TIMESTAMP_SIZE, "[%H:%M:%S]", timeinfo);
}

void process_A(Pipeline *pipes) {
    close(pipes->a_to_b[0]);
    close(pipes->log_pipe[0]);

    srand(time(NULL) ^ getpid());
    for (int i = 0; i < RECORD_COUNT; i++) {
        char record[RECORD_SIZE];
        record[0] = (rand() % 2) ? 'C' : 'D';
        record[1] = '0' + i;
        record[2] = '\0';

        write(pipes->a_to_b[1], record, sizeof(record));

        char timestamp[TIMESTAMP_SIZE];
        char log_msg[LOG_MSG_SIZE];
        generate_timestamp(timestamp);
        snprintf(log_msg, sizeof(log_msg), "%s A sent to B: '%s'\n", timestamp, record);
        write(pipes->log_pipe[1], log_msg, strlen(log_msg));

        usleep(400000); // 400ms delay as specified
    }

    close(pipes->a_to_b[1]);
    close(pipes->log_pipe[1]);
    exit(0);
}

void process_B(Pipeline *pipes) {
    close(pipes->a_to_b[1]);
    close(pipes->b_to_c[0]);
    close(pipes->b_to_d[0]);
    close(pipes->log_pipe[0]);

    char record[RECORD_SIZE];
    for (int i = 0; i < RECORD_COUNT; i++) {
        read(pipes->a_to_b[0], record, sizeof(record));

        char timestamp[TIMESTAMP_SIZE];
        char log_msg[LOG_MSG_SIZE];
        generate_timestamp(timestamp);

        if (record[0] == 'C') {
            write(pipes->b_to_c[1], record, sizeof(record));
            snprintf(log_msg, sizeof(log_msg), "%s B sent to C: '%s'\n", timestamp, record);
        } else {
            write(pipes->b_to_d[1], record, sizeof(record));
            snprintf(log_msg, sizeof(log_msg), "%s B sent to D: '%s'\n", timestamp, record);
        }

        write(pipes->log_pipe[1], log_msg, strlen(log_msg));
        sleep(1); // Strict 1-second delay
    }

    close(pipes->a_to_b[0]);
    close(pipes->b_to_c[1]);
    close(pipes->b_to_d[1]);
    close(pipes->log_pipe[1]);
    exit(0);
}

void process_C(Pipeline *pipes) {
    close(pipes->b_to_c[1]);
    close(pipes->log_pipe[0]);

    char record[RECORD_SIZE];
    while (read(pipes->b_to_c[0], record, sizeof(record)) > 0) {
        char timestamp[TIMESTAMP_SIZE];
        char log_msg[LOG_MSG_SIZE];
        generate_timestamp(timestamp);
        snprintf(log_msg, sizeof(log_msg), "%s C received: '%s'\n", timestamp, record);
        write(pipes->log_pipe[1], log_msg, strlen(log_msg));
    }

    close(pipes->b_to_c[0]);
    close(pipes->log_pipe[1]);
    exit(0);
}

void process_D(Pipeline *pipes) {
    close(pipes->b_to_d[1]);
    close(pipes->log_pipe[0]);

    char record[RECORD_SIZE];
    while (read(pipes->b_to_d[0], record, sizeof(record)) > 0) {
        char timestamp[TIMESTAMP_SIZE];
        char log_msg[LOG_MSG_SIZE];
        generate_timestamp(timestamp);
        snprintf(log_msg, sizeof(log_msg), "%s D received: '%s'\n", timestamp, record);
        write(pipes->log_pipe[1], log_msg, strlen(log_msg));
        
        sleep(5); // Strict 5-second delay
    }

    close(pipes->b_to_d[0]);
    close(pipes->log_pipe[1]);
    exit(0);
}

void logger(Pipeline *pipes, pid_t child_pids[]) {
    close(pipes->log_pipe[1]);

    char buffer[256];
    int logs_received = 0;

    while (logs_received < LOG_LIMIT) {
        int bytes_read = read(pipes->log_pipe[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer);
            fflush(stdout);

            for (int i = 0; i < bytes_read; i++) {
                if (buffer[i] == '\n') logs_received++;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        kill(child_pids[i], SIGTERM);
    }

    close(pipes->log_pipe[0]);
}

int main() {
    Pipeline pipes;
    pid_t child_pids[4];

    if (pipe(pipes.a_to_b) == -1 || pipe(pipes.b_to_c) == -1 || 
        pipe(pipes.b_to_d) == -1 || pipe(pipes.log_pipe) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    if ((child_pids[0] = fork()) == 0) process_A(&pipes);
    if ((child_pids[1] = fork()) == 0) process_B(&pipes);
    if ((child_pids[2] = fork()) == 0) process_C(&pipes);
    if ((child_pids[3] = fork()) == 0) process_D(&pipes);

    close(pipes.a_to_b[0]); close(pipes.a_to_b[1]);
    close(pipes.b_to_c[0]); close(pipes.b_to_c[1]);
    close(pipes.b_to_d[0]); close(pipes.b_to_d[1]);
    close(pipes.log_pipe[1]);

    logger(&pipes, child_pids);

    for (int i = 0; i < 4; i++) {
        waitpid(child_pids[i], NULL, 0);
    }

    printf("Process execution completed successfully.\n");
    return 0;
}