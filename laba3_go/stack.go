package classes

import (
  "fmt"
)

// private node
type stackNode struct {
  data string
  next *stackNode
}

// Stack (PUBLIC)
type Stack struct {
  head *stackNode // private
}

func NewStack() *Stack { // PUBLIC
  return &Stack{head: nil}
}

// Public methods


func (s *Stack) IsEmpty() bool {
  return s.head == nil
}

func (s *Stack) Push(value string) {
  newNode := &stackNode{
    data: value,
    next: s.head,
  }
  s.head = newNode
}

func (s *Stack) Pop() string {
  if s.IsEmpty() {
    return ""
  }
  value := s.head.data
  s.head = s.head.next
  return value
}

func (s *Stack) Top() string {
  if s.IsEmpty() {
    return ""
  }
  return s.head.data
}

func (s *Stack) Clear() {
  for !s.IsEmpty() {
    s.Pop()
  }
}

func (s *Stack) Print() {
  if s.IsEmpty() {
    return
  }
  fmt.Print("Стек (верх -> низ): ")
  cur := s.head
  for cur != nil {
    fmt.Print(cur.data, " ")
    cur = cur.next
  }
  fmt.Println()
}
