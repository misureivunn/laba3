package classes

import (
  "fmt"
)

type Array struct { // PUBLIC
  data     []string // private
  size     int      // private
  capacity int      // private
}

// =======================
// Constructor
// =======================

func NewArray() *Array { // PUBLIC
  return &Array{
    data:     make([]string, 2),
    size:     0,
    capacity: 2,
  }
}

// =======================
// Private helper
// =======================

func (a *Array) resize(newCapacity int) { // PRIVATE
  newData := make([]string, newCapacity)
  copy(newData, a.data)
  a.data = newData
  a.capacity = newCapacity
}

// =======================
// Public methods
// =======================

func (a *Array) PushBack(value string) {
  if a.size >= a.capacity {
    a.resize(a.capacity * 2)
  }
  a.data[a.size] = value
  a.size++
}

func (a *Array) Insert(index int, value string) {
  if index < 0 || index > a.size {
    fmt.Println("Ошибка: индекс вне диапазона")
    return
  }

  a.PushBack("")
  for i := a.size - 1; i > index; i-- {
    a.data[i] = a.data[i-1]
  }
  a.data[index] = value
}

func (a *Array) Delete(index int) {
  if a.size == 0 {
    fmt.Println("Массив пуст")
    return
  }
  if index < 0 || index >= a.size {
    fmt.Println("Ошибка: индекс вне диапазона")
    return
  }

  for i := index; i < a.size-1; i++ {
    a.data[i] = a.data[i+1]
  }
  a.size--
}

func (a *Array) Get(index int) string {
  if index < 0 || index >= a.size {
    return ""
  }
  return a.data[index]
}

func (a *Array) Replace(index int, value string) {
  if index < 0 || index >= a.size {
    return
  }
  a.data[index] = value
}

func (a *Array) Length() int {
  return a.size
}

func (a *Array) Print() {
  if a.size == 0 {
    fmt.Println("Массив пуст")
    return
  }

  fmt.Print("Массив: ")
  for i := 0; i < a.size; i++ {
    fmt.Print(a.data[i], " ")
  }
  fmt.Println()
}

