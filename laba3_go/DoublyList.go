package classes

import (
  "fmt"
)


type nodeDL struct {
  data string
  prev *nodeDL
  next *nodeDL
}


type DoublyList struct {
  head *nodeDL // private поле
  tail *nodeDL // private поле
}



func NewDL() *DoublyList {
  return &DoublyList{}
}


func (l *DoublyList) find(value string) *nodeDL {
  cur := l.head
  for cur != nil {
    if cur.data == value {
      return cur
    }
    cur = cur.next
  }
  return nil
}

func (l *DoublyList) AddHead(value string) {
  newNode := &nodeDL{data: value, next: l.head}
  if l.head != nil {
    l.head.prev = newNode
  } else {
    l.tail = newNode
  }
  l.head = newNode
}

func (l *DoublyList) AddTail(value string) {
  newNode := &nodeDL{data: value, prev: l.tail}
  if l.tail != nil {
    l.tail.next = newNode
  } else {
    l.head = newNode
  }
  l.tail = newNode
}

func (l *DoublyList) AddAfter(target, value string) {
  ptr := l.find(target)
  if ptr == nil {
    return
  }

  newNode := &nodeDL{data: value, prev: ptr, next: ptr.next}
  if ptr.next != nil {
    ptr.next.prev = newNode
  } else {
    l.tail = newNode
  }
  ptr.next = newNode
}

func (l *DoublyList) AddBefore(target, value string) {
  ptr := l.find(target)
  if ptr == nil {
    return
  }

  if ptr.prev == nil {
    l.AddHead(value)
    return
  }

  newNode := &nodeDL{data: value, prev: ptr.prev, next: ptr}
  ptr.prev.next = newNode
  ptr.prev = newNode
}

func (l *DoublyList) DeleteHead() {
  if l.head == nil {
    return
  }

  tmp := l.head
  l.head = tmp.next

  if l.head != nil {
    l.head.prev = nil
  } else {
    l.tail = nil
  }
}

func (l *DoublyList) DeleteTail() {
  if l.tail == nil {
    return
  }

  tmp := l.tail
  l.tail = tmp.prev

  if l.tail != nil {
    l.tail.next = nil
  } else {
    l.head = nil
  }
}

func (l *DoublyList) DeleteAfter(target string) {
  ptr := l.find(target)
  if ptr == nil || ptr.next == nil {
    return
  }

  tmp := ptr.next
  ptr.next = tmp.next

  if tmp.next != nil {
    tmp.next.prev = ptr
  } else {
    l.tail = ptr
  }
}

func (l *DoublyList) DeleteBefore(target string) {
  ptr := l.find(target)
  if ptr == nil || ptr.prev == nil {
    return
  }

  tmp := ptr.prev
  ptr.prev = tmp.prev

  if tmp.prev != nil {
    tmp.prev.next = ptr
  } else {
    l.head = ptr
  }
}

func (l *DoublyList) DeleteByValue(value string) {
  ptr := l.find(value)
  if ptr == nil {
    return
  }

  if ptr == l.head {
    l.DeleteHead()
    return
  }
  if ptr == l.tail {
    l.DeleteTail()
    return
  }

  ptr.prev.next = ptr.next
  ptr.next.prev = ptr.prev
}

func (l *DoublyList) PrintForward() {
  cur := l.head
  for cur != nil {
    fmt.Print(cur.data, " ")
    cur = cur.next
  }
  fmt.Println()
}

func (l *DoublyList) PrintBackward() {
  cur := l.tail
  for cur != nil {
    fmt.Print(cur.data, " ")
    cur = cur.prev
  }
  fmt.Println()
}
