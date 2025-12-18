package classes

import (
    "fmt"
)

type nodeFL struct {
    data string
    next *nodeFL
}

type ForwardList struct {
    head *nodeFL
}

// ===== constructor / destructor =====

func NewFL() *ForwardList {
    return &ForwardList{head: nil}
}

func (l *ForwardList) Clear() {
    l.head = nil // GC всё подчистит
}

// ===== helpers =====

func (l *ForwardList) Find(value string) *nodeFL {
    cur := l.head
    for cur != nil {
        if cur.data == value {
            return cur
        }
        cur = cur.next
    }
    return nil
}

// ===== queries =====

func (l *ForwardList) Contains(value string) bool {
    return l.Find(value) != nil
}

func (l *ForwardList) ToSlice() []string {
    var out []string
    cur := l.head
    for cur != nil {
        out = append(out, cur.data)
        cur = cur.next
    }
    return out
}

// ===== add =====

func (l *ForwardList) AddHead(value string) {
    l.head = &nodeFL{data: value, next: l.head}
}

func (l *ForwardList) AddTail(value string) {
    newNode := &nodeFL{data: value}
    if l.head == nil {
        l.head = newNode
        return
    }
    cur := l.head
    for cur.next != nil {
        cur = cur.next
    }
    cur.next = newNode
}

func (l *ForwardList) AddAfter(target, value string) {
    if l.head == nil {
        fmt.Println("Список пуст")
        return
    }
    ptr := l.Find(target)
    if ptr == nil {
        return
    }
    ptr.next = &nodeFL{data: value, next: ptr.next}
}

func (l *ForwardList) AddBefore(target, value string) {
    if l.head == nil {
        fmt.Println("Список пуст")
        return
    }
    if l.head.data == target {
        l.AddHead(value)
        return
    }

    cur := l.head
    for cur.next != nil && cur.next.data != target {
        cur = cur.next
    }
    if cur.next != nil {
        cur.next = &nodeFL{data: value, next: cur.next}
    }
}

// ===== delete =====

func (l *ForwardList) DeleteHead() {
    if l.head != nil {
        l.head = l.head.next
    }
}

func (l *ForwardList) DeleteTail() {
    if l.head == nil {
        return
    }
    if l.head.next == nil {
        l.head = nil
        return
    }
    cur := l.head
    for cur.next.next != nil {
        cur = cur.next
    }
    cur.next = nil
}

func (l *ForwardList) DeleteAfter(target string) {
    ptr := l.Find(target)
    if ptr == nil || ptr.next == nil {
        return
    }
    ptr.next = ptr.next.next
}

func (l *ForwardList) DeleteBefore(target string) {
    if l.head == nil || l.head.next == nil || l.head.data == target {
        return
    }

    var prev *nodeFL
    cur := l.head

    for cur.next != nil && cur.next.data != target {
        prev = cur
        cur = cur.next
    }

    if cur.next == nil {
        return
    }

    if prev == nil {
        l.DeleteHead()
    } else {
        prev.next = cur.next
    }
}

func (l *ForwardList) DeleteValue(value string) {
    if l.head == nil {
        return
    }
    if l.head.data == value {
        l.DeleteHead()
        return
    }

    cur := l.head
    for cur.next != nil && cur.next.data != value {
        cur = cur.next
    }
    if cur.next != nil {
        cur.next = cur.next.next
    }
}

// ===== print =====

func (l *ForwardList) Print() {
    cur := l.head
    for cur != nil {
        fmt.Print(cur.data, " ")
        cur = cur.next
    }
    fmt.Println()
}
