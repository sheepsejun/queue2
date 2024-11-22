#include <stdio.h>
#include <stdlib.h>

#define Max_Queue 5
typedef int element;

typedef struct {
  element data[Max_Queue];
  int front, rear;
} QueueType;

void error(char *message) {
  printf("%s\n", message);
  exit(1);
}

void init_queue(QueueType *q) {
  q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
  return (q->front == q->rear);
}

int is_full(QueueType *q) {
  return ((q->rear + 1) % Max_Queue == q->front);
}

void queue_print(QueueType *q) {
  printf("QUEUE(front = %d rear = %d) = ", q->front, q->rear);
  if (!is_empty(q)) {
    int i = q->front + 1; // front 뒤부터 시작
    do {
      printf("%d |", q->data[i]);
      i = (i + 1) % Max_Queue; // 순환하면서 출력
    } while (i != (q->rear + 1) % Max_Queue); // rear가 가리키는 항목까지
  }
  printf("\n");
}

void enqueue(QueueType *q, int item) {
  if (is_full(q))
    error("큐가 포화상태입니다.");
  q->rear = (q->rear + 1) % Max_Queue;
  q->data[q->rear] = item;
}

element dequeue(QueueType *q) {
  if (is_empty(q))
    error("큐가 공백상태입니다");
  q->front = (q->front + 1) % Max_Queue;
  return q->data[q->front];
}

element peek(QueueType *q) {
  if (is_empty(q))
    error("큐가 공백상태입니다");
  return q->data[(q->front + 1) % Max_Queue];
}

int main(void) {
  QueueType queue;
  int score;

  init_queue(&queue);
  printf("--데이터 추가 단계--\n");

  while (!is_full(&queue)) {
    printf("정수를 입력하시오 : ");
    scanf("%d", &score);
    enqueue(&queue, score);
    queue_print(&queue);
  }

  printf("큐는 포화상태입니다.\n\n");

  printf("---데이터 삭제 단계---\n");

  while (!is_empty(&queue)) {
    score = dequeue(&queue);
    printf("꺼내진 정수 : %d\n", score);
    queue_print(&queue);
  }
  printf("큐는 공백상태입니다.\n");

  return 0;
}