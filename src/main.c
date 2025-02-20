#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "./vec.h"
#include "./screen.h"
#include "./physics.h"
#include "./ball.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define WIDTH 128
#define HEIGHT 64
#define FPS 60
#define DT (1.0f / FPS)
#define BALL_N 20

bool screen_buffer[WIDTH * HEIGHT];
ball balls[BALL_N];

int rand_range(int min, int max) {
  int r = rand() % (max - min + 1);
  return r + min;
}

int run_ball(FILE* out) {
  srand(time(NULL));

  for (int i = 0; i < BALL_N; i++) {
    vf pos = vf_makeff(rand_range(WIDTH / 4, WIDTH / 4 * 3), rand_range(HEIGHT / 4, HEIGHT / 4 * 3));
    vf vel = vf_makeff((float)rand_range(-100, 100) / 10.0f, (float)rand_range(-100, 100) / 10.0f);
    vf acc = vf_makeff(0.0f, (float)rand_range(10, 100) / 10.0f);

    physics_body body = create_body(pos, vel, acc);

    balls[i] = create_ball(body, (float)rand_range(10, 100) / 10.0f, (float)rand_range(70, 100) / 100.0f);
  }

  while (true) {
    for (int i = 0; i < BALL_N; i++) {
      update_ball(&balls[i], WIDTH, HEIGHT, DT, screen_buffer);
    }

    show(out, screen_buffer, WIDTH, HEIGHT);
    fflush(out);

    usleep(1000 * 1000 / FPS);
    clear(out, screen_buffer, WIDTH, HEIGHT);
  }

  return 0;
}


int main() {
  struct sockaddr_in serveraddr, clientaddr;

  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(8013);

  if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
    fprintf(stderr, "[ERROR] Failed to bind socket: %m\n");
    exit(EXIT_FAILURE);
  }

  listen(listenfd, 5);
  while (1) {
    socklen_t len = sizeof(clientaddr);
    int connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &len);

    if (!fork()) {
      FILE *stream = fdopen(connfd, "r+");
      run_ball(stream);
      fclose(stream);
    }
    close(connfd);
  }
  return 0;
}
