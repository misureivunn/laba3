package classes

import (
  "fmt"
)
// private node

type queueNode struct {
  data string
  next *queueNode
}
// Queue (PUBLIC)

type Queue struct {
  front *queueNode // private
  rear  *queueNode // private
}
=============

func NewQueue() *Queue { // PUBLIC
  return &Queue{
    front: nil,
    rear:  nil,
  }
}

// Public methods

// добавление в конец очереди
func (q *Queue) Push(value string) {
  newNode := &queueNode{
    data: value,
    next: nil,
  }

  if q.rear == nil { // очередь пустая
    q.front = newNode
    q.rear = newNode
    return
  }

  q.rear.next = newNode
  q.rear = newNode
}

// удаление первого элемента
func (q *Queue) Pop() string {
  if q.front == nil {
    return ""
  }

  value := q.front.data
  q.front = q.front.next

  if q.front == nil { // очередь стала пустой
    q.rear = nil
  }

  return value
}

func (q *Queue) IsEmpty() bool {
  return q.front == nil
}

func (q *Queue) Print() {
  if q.IsEmpty() {
    fmt.Println("Очередь пуста")
    return
  }

  fmt.Print("Очередь (слева направо): ")
  cur := q.front
  for cur != nil {
    fmt.Print(cur.data, " ")
    cur = cur.next
  }
  fmt.Println()
}
