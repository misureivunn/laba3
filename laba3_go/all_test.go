package classes

import (
  "io"
  "os"
  "strings"
  "reflect"
  "testing"
  "fmt"
)

func captureOutput(f func()) string {
  old := os.Stdout

  r, w, _ := os.Pipe()
  os.Stdout = w

  f()

  _ = w.Close()
  os.Stdout = old

  out, _ := io.ReadAll(r)
  return string(out)
}

func TestForwardList_AddHeadAndAddTail(t *testing.T) {
  var fl ForwardList

  fl.AddHead("b")
  fl.AddHead("a")
  fl.AddTail("c")

  expected := []string{"a", "b", "c"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }
}

func TestForwardList_Contains(t *testing.T) {
  var fl ForwardList

  if fl.Contains("x") {
    t.Fatal("empty list should not contain elements")
  }

  fl.AddTail("a")
  fl.AddTail("b")

  if !fl.Contains("a") || !fl.Contains("b") {
    t.Fatal("contains returned false for existing element")
  }

  if fl.Contains("c") {
    t.Fatal("contains returned true for missing element")
  }
}

func TestForwardList_AddAfter(t *testing.T) {
  var fl ForwardList

  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddAfter("a", "x")

  expected := []string{"a", "x", "b"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }
}

func TestForwardList_AddBefore(t *testing.T) {
  var fl ForwardList

  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddBefore("b", "x")
  fl.AddBefore("a", "start")

  expected := []string{"start", "a", "x", "b"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }
}

func TestForwardList_DeleteHead(t *testing.T) {
  var fl ForwardList

  fl.DeleteHead() // пустой список

  fl.AddTail("a")
  fl.AddTail("b")
  fl.DeleteHead()

  expected := []string{"b"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }
}

func TestForwardList_DeleteTail(t *testing.T) {
  var fl ForwardList

  fl.DeleteTail() // пустой список

  fl.AddTail("a")
  fl.DeleteTail()

  if len(fl.ToSlice()) != 0 {
    t.Fatal("list should be empty after deleting last element")
  }

  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddTail("c")
  fl.DeleteTail()

  expected := []string{"a", "b"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }
}

func TestForwardList_DeleteAfter(t *testing.T) {
  var fl ForwardList

  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddTail("c")

  fl.DeleteAfter("b")

  expected := []string{"a", "b"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }

  fl.DeleteAfter("c") // после хвоста
  fl.DeleteAfter("x") // несуществующий
}

func TestForwardList_DeleteBefore(t *testing.T) {
  var fl ForwardList

  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddTail("c")

  fl.DeleteBefore("b")

  expected := []string{"b", "c"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }

  fl.DeleteBefore("a") // перед головой
  fl.DeleteBefore("x") // несуществующий
}

func TestForwardList_DeleteValue(t *testing.T) {
  var fl ForwardList

  fl.DeleteValue("x") // пустой список

  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddTail("c")

  fl.DeleteValue("a") // удаление головы
  fl.DeleteValue("c") // удаление хвоста
  fl.DeleteValue("x") // несуществующий

  expected := []string{"b"}
  if !reflect.DeepEqual(fl.ToSlice(), expected) {
    t.Fatalf("expected %v, got %v", expected, fl.ToSlice())
  }
}

func TestForwardList_Clear(t *testing.T) {
  var fl ForwardList

  fl.AddTail("a")
  fl.AddTail("b")
  fl.Clear()

  if len(fl.ToSlice()) != 0 {
    t.Fatal("list should be empty after clear")
  }
}


func TestForwardList_Print(t *testing.T) {
  var fl ForwardList
  fl.AddTail("a")
  fl.AddTail("b")
  fl.AddTail("c")

  out := captureOutput(func() {
    fl.Print()
  })

  expected := "a b c \n"
  if out != expected {
    t.Fatalf("expected %q, got %q", expected, out)
  }
}

//-----------------------------------

/*
========================
DOUBLY LINKED LIST TESTS
========================
*/

func TestDoublyList_AddHeadAndTail(t *testing.T) {
  var list DoublyList

  list.AddHead("b")
  list.AddHead("a")
  list.AddTail("c")

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a b c") {
    t.Fatalf("unexpected output: %s", out)
  }
}

func TestDoublyList_AddAfter(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddAfter("a", "x")

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a x b") {
    t.Errorf("AddAfter failed: %s", out)
  }
}

func TestDoublyList_AddAfterTail(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b") // b — tail

  list.AddAfter("b", "c") // вставка ПОСЛЕ tail

  if list.tail == nil || list.tail.data != "c" {
    t.Fatalf("expected tail to be 'c', got %+v", list.tail)
  }

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a b c") {
    t.Errorf("AddAfter tail failed: %s", out)
  }
}

func TestDoublyList_AddBefore(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddBefore("b", "x")

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a x b") {
    t.Errorf("AddBefore failed: %s", out)
  }
}

func TestDoublyList_DeleteHead(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")

  list.DeleteHead()

  out := captureOutput(func() {
    list.PrintForward()
  })

  if strings.Contains(out, "a") {
    t.Errorf("DeleteHead failed: %s", out)
  }
}

func TestDoublyList_DeleteTail(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")

  list.DeleteTail()

  out := captureOutput(func() {
    list.PrintForward()
  })

  if strings.Contains(out, "b") {
    t.Errorf("DeleteTail failed: %s", out)
  }
}

func TestDoublyList_DeleteAfter(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddTail("c")

  list.DeleteAfter("a")

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a c") {
    t.Errorf("DeleteAfter failed: %s", out)
  }
}

func TestDoublyList_DeleteAfter_TailCase(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddTail("c") // tail

  // удаляем элемент ПОСЛЕ "b" → удаляется "c"
  list.DeleteAfter("b")

  // tail должен стать "b"
  if list.tail == nil || list.tail.data != "b" {
    t.Fatalf("expected tail to be 'b', got %+v", list.tail)
  }

  // проверяем целостность
  if list.tail.next != nil {
    t.Errorf("tail.next should be nil")
  }

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a b") {
    t.Errorf("DeleteAfter tail case failed: %s", out)
  }
}

func TestDoublyList_DeleteByValue_NotFound(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")

  list.DeleteByValue("x") // такого нет

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a b") {
    t.Errorf("list changed when deleting non-existing value: %s", out)
  }
}

func TestDoublyList_DeleteByValue_Head(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")

  list.DeleteByValue("a") // head

  if list.head == nil || list.head.data != "b" {
    t.Fatalf("DeleteByValue head failed")
  }
}

func TestDoublyList_DeleteByValue_Tail(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")

  list.DeleteByValue("b") // tail

  if list.tail == nil || list.tail.data != "a" {
    t.Fatalf("DeleteByValue tail failed")
  }
}
func TestDoublyList_DeleteBefore(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddTail("c")

  list.DeleteBefore("c")

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a c") {
    t.Errorf("DeleteBefore failed: %s", out)
  }
}

func TestDoublyList_DeleteByValue(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddTail("c")

  list.DeleteByValue("b")

  out := captureOutput(func() {
    list.PrintForward()
  })

  if strings.Contains(out, "b") {
    t.Errorf("DeleteByValue failed: %s", out)
  }
}

func TestDoublyList_DeleteByValue_Middle(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddTail("c")

  list.DeleteByValue("b") // middle

  out := captureOutput(func() {
    list.PrintForward()
  })

  if !strings.Contains(out, "a c") {
    t.Errorf("DeleteByValue middle failed: %s", out)
  }

  if list.head.next != list.tail || list.tail.prev != list.head {
    t.Errorf("links are broken after middle delete")
  }
}

func TestDoublyList_PrintBackward(t *testing.T) {
  var list DoublyList

  list.AddTail("a")
  list.AddTail("b")
  list.AddTail("c")

  out := captureOutput(func() {
    list.PrintBackward()
  })

  if !strings.Contains(out, "c b a") {
    t.Errorf("PrintBackward failed: %s", out)
  }
}

func TestDoublyList_EmptyListPrint(t *testing.T) {
  var list DoublyList

  out := captureOutput(func() {
    list.PrintForward()
  })

  if out == "" {
    t.Errorf("expected empty list message, got empty output")
  }
}

//-------------------------------------------------------
func TestArray_NewArray(t *testing.T) {
    arr := NewArray()
    
    if arr.Length() != 0 {
        t.Errorf("Новый массив должен быть пустым")
    }
}

func TestArray_PushBack(t *testing.T) {
    arr := NewArray()
    
    arr.PushBack("first")
    arr.PushBack("second")
    
    if arr.Length() != 2 {
        t.Errorf("Длина должна быть 2")
    }
    
    if arr.Get(0) != "first" || arr.Get(1) != "second" {
        t.Errorf("Неверные значения элементов")
    }
}

func TestArray_GetInvalidIndex(t *testing.T) {
    arr := NewArray()
    arr.PushBack("test")
    
    if arr.Get(-1) != "" {
        t.Errorf("Get(-1) должен возвращать пустую строку")
    }
    
    if arr.Get(5) != "" {
        t.Errorf("Get(5) должен возвращать пустую строку")
    }
}

func TestArray_Length(t *testing.T) {
    arr := NewArray()
    
    if arr.Length() != 0 {
        t.Errorf("Длина нового массива должна быть 0")
    }
    
    arr.PushBack("a")
    arr.PushBack("b")
    
    if arr.Length() != 2 {
        t.Errorf("Длина должна быть 2")
    }
}

func TestArray_Insert(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    arr.PushBack("c")
    
    arr.Insert(1, "b")
    
    if arr.Length() != 3 {
        t.Errorf("Длина должна быть 3")
    }
    
    if arr.Get(0) != "a" || arr.Get(1) != "b" || arr.Get(2) != "c" {
        t.Errorf("Неверный порядок элементов после Insert")
    }
}

func TestArray_InsertAtStart(t *testing.T) {
    arr := NewArray()
    arr.PushBack("b")
    arr.PushBack("c")
    
    arr.Insert(0, "a")
    
    if arr.Get(0) != "a" {
        t.Errorf("Первый элемент должен быть 'a'")
    }
}

func TestArray_InsertAtEnd(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    arr.PushBack("b")
    
    arr.Insert(2, "c")
    
    if arr.Get(2) != "c" {
        t.Errorf("Последний элемент должен быть 'c'")
    }
}

func TestArray_InsertInvalidIndex(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    
    // Захватываем вывод
    out := captureOutput(func() {
        arr.Insert(-1, "b")
        arr.Insert(10, "c")
    })
    
    if !strings.Contains(out, "Ошибка: индекс вне диапазона") {
        t.Errorf("Должна быть ошибка для неверного индекса")
    }
    
    if arr.Length() != 1 {
        t.Errorf("Неверный индекс не должен добавлять элементы")
    }
}

func TestArray_Delete(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    arr.PushBack("b")
    arr.PushBack("c")
    
    arr.Delete(1)
    
    if arr.Length() != 2 {
        t.Errorf("Длина должна быть 2 после удаления")
    }
    
    if arr.Get(0) != "a" || arr.Get(1) != "c" {
        t.Errorf("Неверные элементы после удаления")
    }
}

func TestArray_DeleteFirst(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    arr.PushBack("b")
    arr.PushBack("c")
    
    arr.Delete(0)
    
    if arr.Length() != 2 {
        t.Errorf("Длина должна быть 2")
    }
    
    if arr.Get(0) != "b" {
        t.Errorf("Первый элемент должен быть 'b'")
    }
}

func TestArray_DeleteLast(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    arr.PushBack("b")
    arr.PushBack("c")
    
    arr.Delete(2)
    
    if arr.Length() != 2 {
        t.Errorf("Длина должна быть 2")
    }
    
    if arr.Get(1) != "b" {
        t.Errorf("Последний элемент должен быть 'b'")
    }
}

func TestArray_DeleteInvalidIndex(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    
    out := captureOutput(func() {
        arr.Delete(-1)
    })
    
    if !strings.Contains(out, "Ошибка: индекс вне диапазона") {
        t.Errorf("Должна быть ошибка для неверного индекса")
    }
    
    if arr.Length() != 1 {
        t.Errorf("Длина не должна измениться")
    }
}

func TestArray_DeleteEmpty(t *testing.T) {
    arr := NewArray()
    
    out := captureOutput(func() {
        arr.Delete(0)
    })
    
    if !strings.Contains(out, "Массив пуст") {
        t.Errorf("Должно быть сообщение о пустом массиве")
    }
}

func TestArray_Replace(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    arr.PushBack("b")
    arr.PushBack("c")
    
    arr.Replace(1, "x")
    
    if arr.Get(1) != "x" {
        t.Errorf("Элемент должен быть заменен на 'x'")
    }
    
    // Остальные элементы не должны измениться
    if arr.Get(0) != "a" || arr.Get(2) != "c" {
        t.Errorf("Другие элементы не должны измениться")
    }
}

func TestArray_ReplaceInvalidIndex(t *testing.T) {
    arr := NewArray()
    arr.PushBack("a")
    
    arr.Replace(-1, "b")
    arr.Replace(5, "c")
    
    if arr.Length() != 1 || arr.Get(0) != "a" {
        t.Errorf("Неверный индекс не должен менять массив")
    }
}

func TestArray_Print(t *testing.T) {
    arr := NewArray()
    arr.PushBack("hello")
    arr.PushBack("world")
    
    out := captureOutput(func() {
        arr.Print()
    })
    
    if !strings.Contains(out, "Массив: hello world") {
        t.Errorf("Неверный вывод Print: %s", out)
    }
}

func TestArray_PrintEmpty(t *testing.T) {
    arr := NewArray()
    
    out := captureOutput(func() {
        arr.Print()
    })
    
    if !strings.Contains(out, "Массив пуст") {
        t.Errorf("Должно быть сообщение о пустом массиве: %s", out)
    }
}

func TestArray_Resize(t *testing.T) {
    arr := NewArray()
    
    // Начальная capacity = 2
    for i := 0; i < 10; i++ {
        arr.PushBack("test")
    }
    
    if arr.Length() != 10 {
        t.Errorf("Должно быть 10 элементов")
    }
    
    // Проверяем, что все элементы на месте
    for i := 0; i < 10; i++ {
        if arr.Get(i) != "test" {
            t.Errorf("Элемент %d неверный", i)
        }
    }
}

func TestArray_InsertAndDelete(t *testing.T) {
    arr := NewArray()
    
    // Добавляем
    arr.PushBack("a")
    arr.PushBack("c")
    arr.Insert(1, "b")
    
    // Удаляем
    arr.Delete(0)
    
    if arr.Length() != 2 {
        t.Errorf("Длина должна быть 2")
    }
    
    if arr.Get(0) != "b" || arr.Get(1) != "c" {
        t.Errorf("Неверные элементы после операций")
    }
}

func TestArray_MultipleOperations(t *testing.T) {
    arr := NewArray()
    
    // Серия операций
    arr.PushBack("a")
    arr.PushBack("b")
    arr.Insert(1, "x")
    arr.Delete(0)
    arr.Replace(0, "y")
    arr.PushBack("z")
    
    if arr.Length() != 3 {
        t.Errorf("Длина должна быть 3")
    }
    
    if arr.Get(0) != "y" || arr.Get(1) != "b" || arr.Get(2) != "z" {
        t.Errorf("Неверные элементы: %s %s %s", arr.Get(0), arr.Get(1), arr.Get(2))
    }
}
//---------------------------------------------------

func TestQueue_NewQueue(t *testing.T) {
  q := NewQueue()
  
  if !q.IsEmpty() {
    t.Errorf("Новая очередь должна быть пустой")
  }
}

func TestQueue_Push(t *testing.T) {
  q := NewQueue()
  
  q.Push("first")
  if q.IsEmpty() {
    t.Errorf("Очередь не должна быть пустой после Push")
  }
  
  q.Push("second")
  q.Push("third")
  
  // Проверяем последовательность извлечения
  if q.Pop() != "first" {
    t.Errorf("Первым должен извлекаться 'first'")
  }
  if q.Pop() != "second" {
    t.Errorf("Вторым должен извлекаться 'second'")
  }
  if q.Pop() != "third" {
    t.Errorf("Третьим должен извлекаться 'third'")
  }
}

func TestQueue_PushToEmpty(t *testing.T) {
  q := NewQueue()
  
  q.Push("only")
  
  if q.Pop() != "only" {
    t.Errorf("Должен извлекаться 'only'")
  }
  
  if !q.IsEmpty() {
    t.Errorf("Очередь должна быть пустой после извлечения единственного элемента")
  }
}

func TestQueue_PopFromEmpty(t *testing.T) {
  q := NewQueue()
  
  value := q.Pop()
  if value != "" {
    t.Errorf("Pop из пустой очереди должен возвращать пустую строку")
  }
}

func TestQueue_PushPopSequence(t *testing.T) {
  q := NewQueue()
  
  // Добавляем и извлекаем несколько раз
  q.Push("a")
  q.Push("b")
  if q.Pop() != "a" {
    t.Errorf("Ожидалось 'a'")
  }
  
  q.Push("c")
  if q.Pop() != "b" {
    t.Errorf("Ожидалось 'b'")
  }
  if q.Pop() != "c" {
    t.Errorf("Ожидалось 'c'")
  }
  
  if !q.IsEmpty() {
    t.Errorf("Очередь должна быть пустой")
  }
}

func TestQueue_IsEmpty(t *testing.T) {
  q := NewQueue()
  
  if !q.IsEmpty() {
    t.Errorf("Новая очередь должна быть пустой")
  }
  
  q.Push("test")
  if q.IsEmpty() {
    t.Errorf("Очередь не должна быть пустой после Push")
  }
  
  q.Pop()
  if !q.IsEmpty() {
    t.Errorf("Очередь должна быть пустой после Pop")
  }
}

func TestQueue_PrintEmpty(t *testing.T) {
  q := NewQueue()
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  q.Print()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  if !strings.Contains(string(out), "Очередь пуста") {
    t.Errorf("Должно быть сообщение 'Очередь пуста'")
  }
}

func TestQueue_PrintWithElements(t *testing.T) {
  q := NewQueue()
  q.Push("apple")
  q.Push("banana")
  q.Push("cherry")
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  q.Print()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  output := string(out)
  
  if !strings.Contains(output, "Очередь (слева направо):") {
    t.Errorf("Должен быть заголовок вывода")
  }
  
  if !strings.Contains(output, "apple") ||
     !strings.Contains(output, "banana") ||
     !strings.Contains(output, "cherry") {
    t.Errorf("Все элементы должны быть в выводе")
  }
}

func TestQueue_FIFOOrder(t *testing.T) {
  q := NewQueue()
  
  items := []string{"first", "second", "third", "fourth"}
  for _, item := range items {
    q.Push(item)
  }
  
  for _, expected := range items {
    actual := q.Pop()
    if actual != expected {
      t.Errorf("Ожидалось %s, получено %s", expected, actual)
    }
  }
  
  if !q.IsEmpty() {
    t.Errorf("Очередь должна быть пустой после извлечения всех элементов")
  }
}

func TestQueue_MultipleOperations(t *testing.T) {
  q := NewQueue()
  
  // Добавляем несколько
  q.Push("a")
  q.Push("b")
  q.Push("c")
  
  // Извлекаем один
  if q.Pop() != "a" {
    t.Errorf("Ожидалось 'a'")
  }
  
  // Добавляем еще
  q.Push("d")
  q.Push("e")
  
  // Извлекаем все
  expected := []string{"b", "c", "d", "e"}
  for _, exp := range expected {
    if q.Pop() != exp {
      t.Errorf("Ожидалось %s", exp)
    }
  }
  
  if !q.IsEmpty() {
    t.Errorf("Очередь должна быть пустой")
  }
}

func TestQueue_PopAllFromNonEmpty(t *testing.T) {
  q := NewQueue()
  
  q.Push("x")
  q.Push("y")
  q.Push("z")
  
  // Извлекаем все
  q.Pop()
  q.Pop()
  q.Pop()
  
  // Проверяем, что очередь пуста
  if !q.IsEmpty() {
    t.Errorf("Очередь должна быть пустой")
  }
  
  // Пробуем извлечь из пустой
  if q.Pop() != "" {
    t.Errorf("Pop из пустой должен возвращать пустую строку")
  }
}

func TestQueue_PrintAfterOperations(t *testing.T) {
  q := NewQueue()
  
  // Добавляем и удаляем
  q.Push("one")
  q.Push("two")
  q.Pop()
  q.Push("three")
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  q.Print()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  output := string(out)
  
  // Проверяем, что остались правильные элементы
  if !strings.Contains(output, "two") || !strings.Contains(output, "three") {
    t.Errorf("Должны быть элементы 'two' и 'three'")
  }
  
  if strings.Contains(output, "one") {
    t.Errorf("Элемент 'one' уже удален, не должен отображаться")
  }
}
//-----------------------------------------------

func TestStack_NewStack(t *testing.T) {
  s := NewStack()
  
  if !s.IsEmpty() {
    t.Errorf("Новый стек должен быть пустым")
  }
}

func TestStack_Push(t *testing.T) {
  s := NewStack()
  
  s.Push("first")
  if s.IsEmpty() {
    t.Errorf("Стек не должен быть пустым после Push")
  }
  
  s.Push("second")
  s.Push("third")
  
  // Проверяем порядок извлечения (LIFO)
  if s.Pop() != "third" {
    t.Errorf("Первым должен извлекаться 'third' (LIFO)")
  }
  if s.Pop() != "second" {
    t.Errorf("Вторым должен извлекаться 'second'")
  }
  if s.Pop() != "first" {
    t.Errorf("Третьим должен извлекаться 'first'")
  }
}

func TestStack_PushToEmpty(t *testing.T) {
  s := NewStack()
  
  s.Push("only")
  
  if s.Pop() != "only" {
    t.Errorf("Должен извлекаться 'only'")
  }
  
  if !s.IsEmpty() {
    t.Errorf("Стек должен быть пустым после извлечения единственного элемента")
  }
}

func TestStack_PopFromEmpty(t *testing.T) {
  s := NewStack()
  
  value := s.Pop()
  if value != "" {
    t.Errorf("Pop из пустого стека должен возвращать пустую строку")
  }
}

func TestStack_Top(t *testing.T) {
  s := NewStack()
  
  // Top на пустом стеке
  if s.Top() != "" {
    t.Errorf("Top пустого стека должен возвращать пустую строку")
  }
  
  s.Push("first")
  if s.Top() != "first" {
    t.Errorf("Top должен возвращать 'first'")
  }
  
  s.Push("second")
  if s.Top() != "second" {
    t.Errorf("Top должен возвращать 'second'")
  }
  
  // Top не должен удалять элемент
  if s.Pop() != "second" {
    t.Errorf("Pop должен возвращать 'second'")
  }
  if s.Top() != "first" {
    t.Errorf("Top теперь должен возвращать 'first'")
  }
}

func TestStack_IsEmpty(t *testing.T) {
  s := NewStack()
  
  if !s.IsEmpty() {
    t.Errorf("Новый стек должен быть пустым")
  }
  
  s.Push("test")
  if s.IsEmpty() {
    t.Errorf("Стек не должен быть пустым после Push")
  }
  
  s.Pop()
  if !s.IsEmpty() {
    t.Errorf("Стек должен быть пустым после Pop")
  }
}

func TestStack_Clear(t *testing.T) {
  s := NewStack()
  
  // Clear пустого стека
  s.Clear()
  if !s.IsEmpty() {
    t.Errorf("Стек должен быть пустым после Clear")
  }
  
  // Clear непустого стека
  s.Push("a")
  s.Push("b")
  s.Push("c")
  
  s.Clear()
  
  if !s.IsEmpty() {
    t.Errorf("Стек должен быть пустым после Clear")
  }
  
  if s.Pop() != "" {
    t.Errorf("Pop после Clear должен возвращать пустую строку")
  }
}

func TestStack_Print(t *testing.T) {
  s := NewStack()
  s.Push("cherry")
  s.Push("banana")
  s.Push("apple")
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  s.Print()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  output := string(out)
  
  if !strings.Contains(output, "Стек (верх -> низ):") {
    t.Errorf("Должен быть заголовок вывода")
  }
  
  // Проверяем порядок (LIFO - apple должен быть первым)
  expectedOrder := "apple banana cherry"
  cleanOutput := strings.TrimSpace(output)
  if !strings.Contains(cleanOutput, expectedOrder) {
    t.Errorf("Неверный порядок элементов. Ожидалось '%s' в выводе, получено: %s", expectedOrder, cleanOutput)
  }
}

func TestStack_LIFOOrder(t *testing.T) {
  s := NewStack()
  
  items := []string{"first", "second", "third", "fourth"}
  for _, item := range items {
    s.Push(item)
  }
  
  // Извлекаем в обратном порядке (LIFO)
  for i := len(items) - 1; i >= 0; i-- {
    actual := s.Pop()
    if actual != items[i] {
      t.Errorf("Ожидалось %s, получено %s", items[i], actual)
    }
  }
  
  if !s.IsEmpty() {
    t.Errorf("Стек должен быть пустым после извлечения всех элементов")
  }
}
//------------------------------------------

func TestHashTableOpen_NewHashTableOpen(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Проверяем, что все ячейки пустые
  for i := 0; i < openTableSize; i++ {
    if ht.table[i].used {
      t.Errorf("Новая таблица должна иметь все ячейки неиспользованными")
    }
  }
}

func TestHashTableOpen_Insert(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Вставка первого элемента
  inserted := ht.Insert("value1", "key1")
  if !inserted {
    t.Errorf("Вставка должна быть успешной")
  }
  
  // Проверяем, что элемент действительно добавлен
  if !ht.Contains("key1") {
    t.Errorf("Таблица должна содержать ключ 'key1'")
  }
  if ht.Get("key1") != "value1" {
    t.Errorf("Значение для 'key1' должно быть 'value1'")
  }
}

func TestHashTableOpen_InsertEmptyKey(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Попытка вставки с пустым ключом
  inserted := ht.Insert("value", "")
  if inserted {
    t.Errorf("Вставка с пустым ключом должна быть неуспешной")
  }
}

func TestHashTableOpen_InsertDuplicateKey(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Первая вставка
  ht.Insert("value1", "key1")
  
  // Вторая вставка с тем же ключом
  inserted := ht.Insert("value2", "key1")
  if inserted {
    t.Errorf("Дубликат ключа не должен вставляться")
  }
  
  // Проверяем, что старое значение осталось
  if ht.Get("key1") != "value1" {
    t.Errorf("Значение не должно меняться при дубликате ключа")
  }
}

func TestHashTableOpen_GetExisting(t *testing.T) {
  ht := NewHashTableOpen()
  ht.Insert("apple", "fruit")
  ht.Insert("carrot", "vegetable")
  
  value := ht.Get("fruit")
  if value != "apple" {
    t.Errorf("Ожидалось 'apple', получено '%s'", value)
  }
  
  value = ht.Get("vegetable")
  if value != "carrot" {
    t.Errorf("Ожидалось 'carrot', получено '%s'", value)
  }
}

func TestHashTableOpen_GetNonExisting(t *testing.T) {
  ht := NewHashTableOpen()
  ht.Insert("test", "key1")
  
  // Ключ не существует
  value := ht.Get("nonexistent")
  if value != "" {
    t.Errorf("Для несуществующего ключа должна возвращаться пустая строка")
  }
  
  // Пустая таблица
  ht2 := NewHashTableOpen()
  value = ht2.Get("anykey")
  if value != "" {
    t.Errorf("Для пустой таблицы должна возвращаться пустая строка")
  }
}

func TestHashTableOpen_Contains(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Проверка на пустой таблице
  if ht.Contains("key") {
    t.Errorf("Пустая таблица не должна содержать ключи")
  }
  
  // Добавляем и проверяем
  ht.Insert("value", "key")
  if !ht.Contains("key") {
    t.Errorf("Таблица должна содержать добавленный ключ")
  }
  
  // Проверка несуществующего ключа
  if ht.Contains("otherkey") {
    t.Errorf("Не должна содержать недобавленный ключ")
  }
}

func TestHashTableOpen_Remove(t *testing.T) {
  ht := NewHashTableOpen()
  ht.Insert("value1", "key1")
  ht.Insert("value2", "key2")
  
  // Удаление существующего ключа
  removed := ht.Remove("key1")
  if !removed {
    t.Errorf("Удаление должно быть успешным")
  }
  
  // Проверяем, что ключ удален
  if ht.Contains("key1") {
    t.Errorf("Ключ должен быть удален")
  }
  if ht.Get("key1") != "" {
    t.Errorf("Значение удаленного ключа должно быть пустым")
  }
  
  // Проверяем, что второй ключ остался
  if !ht.Contains("key2") {
    t.Errorf("Другой ключ не должен быть затронут")
  }
}

func TestHashTableOpen_RemoveNonExisting(t *testing.T) {
  ht := NewHashTableOpen()
  ht.Insert("value", "key")
  
  // Удаление несуществующего ключа
  removed := ht.Remove("nonexistent")
  if removed {
    t.Errorf("Удаление несуществующего ключа должно быть неуспешным")
  }
  
  // Удаление из пустой таблицы
  ht2 := NewHashTableOpen()
  removed = ht2.Remove("anykey")
  if removed {
    t.Errorf("Удаление из пустой таблицы должно быть неуспешным")
  }
}

func TestHashTableOpen_CollisionHandling(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Создаем коллизию (если hashFun одинаков для ключей)
  // Для теста используем DebugIndex чтобы проверить
  key1 := "ab"
  key2 := "ba"
  
  // Вставляем первый ключ
  ht.Insert("value1", key1)
  
  // Второй ключ должен найти другое место из-за линейного пробирования
  ht.Insert("value2", key2)
  
  // Проверяем, что оба существуют
  if !ht.Contains(key1) {
    t.Errorf("Первый ключ должен существовать")
  }
  if !ht.Contains(key2) {
    t.Errorf("Второй ключ должен существовать после коллизии")
  }
  
  // Проверяем значения
  if ht.Get(key1) != "value1" {
    t.Errorf("Неверное значение для первого ключа")
  }
  if ht.Get(key2) != "value2" {
    t.Errorf("Неверное значение для второго ключа")
  }
}

func TestHashTableOpen_FullTable(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Заполняем таблицу полностью
  for i := 0; i < openTableSize; i++ {
    key := fmt.Sprintf("key%d", i)
    value := fmt.Sprintf("value%d", i)
    inserted := ht.Insert(value, key)
    if !inserted {
      t.Errorf("Вставка %d должна быть успешной", i)
    }
  }
  
  // Попытка вставить в полную таблицу
  inserted := ht.Insert("extra", "extrakey")
  if inserted {
    t.Errorf("Вставка в полную таблицу должна быть неуспешной")
  }
}

func TestHashTableOpen_RemoveAndReinsert(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Добавляем и удаляем
  ht.Insert("first", "key1")
  ht.Remove("key1")
  
  // Добавляем снова в ту же ячейку
  inserted := ht.Insert("second", "key1")
  if !inserted {
    t.Errorf("Повторная вставка после удаления должна быть успешной")
  }
  
  if ht.Get("key1") != "second" {
    t.Errorf("Новое значение должно быть 'second'")
  }
}

func TestHashTableOpen_PrintTable(t *testing.T) {
  ht := NewHashTableOpen()
  ht.Insert("apple", "fruit")
  ht.Insert("carrot", "vegetable")
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  ht.PrintTable()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  output := string(out)
  
  // Проверяем заголовок
  if !strings.Contains(output, "Хэш-таблица (ключ -> значение):") {
    t.Errorf("Должен быть заголовок таблицы")
  }
  
  // Проверяем наличие наших данных
  if !strings.Contains(output, "fruit") || !strings.Contains(output, "apple") {
    t.Errorf("Должны отображаться ключ и значение 'fruit' -> 'apple'")
  }
  
  if !strings.Contains(output, "vegetable") || !strings.Contains(output, "carrot") {
    t.Errorf("Должны отображаться ключ и значение 'vegetable' -> 'carrot'")
  }
}

func TestHashTableOpen_PrintEmptyTable(t *testing.T) {
  ht := NewHashTableOpen()
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  ht.PrintTable()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  output := string(out)
  
  // Проверяем, что вывод содержит заголовок и пустые ячейки
  if !strings.Contains(output, "Хэш-таблица") {
    t.Errorf("Должен быть заголовок таблицы")
  }
  
  // Проверяем наличие символа '-' для пустых ячеек
  if !strings.Contains(output, "-") {
    t.Errorf("Должны быть отображены пустые ячейки")
  }
}

func TestHashTableOpen_ComplexOperations(t *testing.T) {
  ht := NewHashTableOpen()
  
  // Добавляем несколько элементов
  ht.Insert("v1", "k1")
  ht.Insert("v2", "k2")
  ht.Insert("v3", "k3")
  
  // Удаляем один
  ht.Remove("k2")
  
  // Проверяем состояние
  if !ht.Contains("k1") {
    t.Errorf("k1 должен существовать")
  }
  if ht.Contains("k2") {
    t.Errorf("k2 должен быть удален")
  }
  if !ht.Contains("k3") {
    t.Errorf("k3 должен существовать")
  }
  
  // Добавляем новый ключ на место удаленного
  ht.Insert("v4", "k4")
  
  // Проверяем все
  if ht.Get("k1") != "v1"||  ht.Get("k3") != "v3" || ht.Get("k4") != "v4" {
    t.Errorf("Неверные значения после операций")
  }
}

//-----------------------------------------------------


func TestChainHashTable_NewChainHashTable(t *testing.T) {
  ht := NewChainHashTable()
  
  // Проверяем, что все ячейки пустые (nil)
  for i := 0; i < chainTableSize; i++ {
    if ht.table[i] != nil {
      t.Errorf("Новая таблица должна иметь все цепочки пустыми")
    }
  }
}

func TestChainHashTable_Insert(t *testing.T) {
  ht := NewChainHashTable()
  
  // Вставка первого элемента
  inserted := ht.Insert("key1", "value1")
  if !inserted {
    t.Errorf("Вставка должна быть успешной")
  }
  
  // Проверяем, что элемент действительно добавлен
  if !ht.Contains("key1") {
    t.Errorf("Таблица должна содержать ключ 'key1'")
  }
  if ht.Get("key1") != "value1" {
    t.Errorf("Значение для 'key1' должно быть 'value1'")
  }
}

func TestChainHashTable_InsertDuplicate(t *testing.T) {
  ht := NewChainHashTable()
  
  // Первая вставка
  ht.Insert("key1", "value1")
  
  // Вторая вставка с тем же ключом
  inserted := ht.Insert("key1", "value2")
  if inserted {
    t.Errorf("Дубликат ключа не должен вставляться")
  }
  
  // Проверяем, что старое значение осталось
  if ht.Get("key1") != "value1" {
    t.Errorf("Значение не должно меняться при дубликате ключа")
  }
}

func TestChainHashTable_GetExisting(t *testing.T) {
  ht := NewChainHashTable()
  ht.Insert("fruit", "apple")
  ht.Insert("vegetable", "carrot")
  
  value := ht.Get("fruit")
  if value != "apple" {
    t.Errorf("Ожидалось 'apple', получено '%s'", value)
  }
  
  value = ht.Get("vegetable")
  if value != "carrot" {
    t.Errorf("Ожидалось 'carrot', получено '%s'", value)
  }
}

func TestChainHashTable_GetNonExisting(t *testing.T) {
  ht := NewChainHashTable()
  ht.Insert("key1", "value1")
  
  // Ключ не существует
  value := ht.Get("nonexistent")
  if value != "" {
    t.Errorf("Для несуществующего ключа должна возвращаться пустая строка")
  }
  
  // Пустая таблица
  ht2 := NewChainHashTable()
  value = ht2.Get("anykey")
  if value != "" {
    t.Errorf("Для пустой таблицы должна возвращаться пустая строка")
  }
}

func TestChainHashTable_Contains(t *testing.T) {
  ht := NewChainHashTable()
  
  // Проверка на пустой таблице
  if ht.Contains("key") {
    t.Errorf("Пустая таблица не должна содержать ключи")
  }
  
  // Добавляем и проверяем
  ht.Insert("key", "value")
  if !ht.Contains("key") {
    t.Errorf("Таблица должна содержать добавленный ключ")
  }
  
  // Проверка несуществующего ключа
  if ht.Contains("otherkey") {
    t.Errorf("Не должна содержать недобавленный ключ")
  }
}

func TestChainHashTable_Remove(t *testing.T) {
  ht := NewChainHashTable()
  ht.Insert("key1", "value1")
  ht.Insert("key2", "value2")
  
  // Удаление существующего ключа
  ht.Remove("key1")
  
  // Проверяем, что ключ удален
  if ht.Contains("key1") {
    t.Errorf("Ключ должен быть удален")
  }
  if ht.Get("key1") != "" {
    t.Errorf("Значение удаленного ключа должно быть пустым")
  }
  
  // Проверяем, что второй ключ остался
  if !ht.Contains("key2") {
    t.Errorf("Другой ключ не должен быть затронут")
  }
}

func TestChainHashTable_RemoveNonExisting(t *testing.T) {
  ht := NewChainHashTable()
  ht.Insert("key", "value")
  
  // Удаление несуществующего ключа (не должно паниковать)
  ht.Remove("nonexistent")
  
  // Проверяем, что существующий ключ остался
  if !ht.Contains("key") {
    t.Errorf("Существующий ключ не должен быть затронут")
  }
  
  // Удаление из пустой таблицы
  ht2 := NewChainHashTable()
  ht2.Remove("anykey")
  // Не должно паниковать
}

//----------------------------------------------------

func TestCompleteBinaryTree_NewTree(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  if tree.root != nil {
    t.Errorf("Новое дерево должно иметь nil корень")
  }
}

func TestCompleteBinaryTree_InsertFirst(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  tree.Insert(10)
  
  if tree.root == nil {
    t.Errorf("Корень не должен быть nil после вставки")
  }
  if tree.root.data != 10 {
    t.Errorf("Корень должен содержать значение 10")
  }
}

func TestCompleteBinaryTree_InsertMultiple(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  // Вставляем несколько значений
  tree.Insert(1)
  tree.Insert(2)
  tree.Insert(3)
  tree.Insert(4)
  tree.Insert(5)
  
  // Проверяем, что все значения существуют
  for i := 1; i <= 5; i++ {
    if !tree.Search(i) {
      t.Errorf("Дерево должно содержать значение %d", i)
    }
  }
}

func TestCompleteBinaryTree_SearchEmpty(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  if tree.Search(10) {
    t.Errorf("Поиск в пустом дереве должен возвращать false")
  }
}

func TestCompleteBinaryTree_SearchExisting(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  tree.Insert(5)
  tree.Insert(3)
  tree.Insert(7)
  tree.Insert(2)
  tree.Insert(4)
  tree.Insert(6)
  tree.Insert(8)
  
  // Проверяем существующие значения
  if !tree.Search(5) {
    t.Errorf("Дерево должно содержать 5")
  }
  if !tree.Search(3) {
    t.Errorf("Дерево должно содержать 3")
  }
  if !tree.Search(7) {
    t.Errorf("Дерево должно содержать 7")
  }
  if !tree.Search(2) {
    t.Errorf("Дерево должно содержать 2")
  }
  if !tree.Search(8) {
    t.Errorf("Дерево должно содержать 8")
  }
}

func TestCompleteBinaryTree_SearchNonExisting(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  tree.Insert(1)
  tree.Insert(2)
  tree.Insert(3)
  
  if tree.Search(10) {
    t.Errorf("Дерево не должно содержать 10")
  }
  if tree.Search(0) {
    t.Errorf("Дерево не должно содержать 0")
  }
}

func TestCompleteBinaryTree_IsCompleteEmpty(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  if !tree.IsComplete() {
    t.Errorf("Пустое дерево должно быть полным")
  }
}

func TestCompleteBinaryTree_IsCompleteSingle(t *testing.T) {
  tree := NewCompleteBinaryTree()
  tree.Insert(1)
  
  if !tree.IsComplete() {
    t.Errorf("Дерево с одним элементом должно быть полным")
  }
}

func TestCompleteBinaryTree_IsCompleteSmall(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  // Создаем полное бинарное дерево
  tree.Insert(1)  // корень
  tree.Insert(2)  // левый
  tree.Insert(3)  // правый
  
  if !tree.IsComplete() {
    t.Errorf("Маленькое полное дерево должно быть полным")
  }
}

func TestCompleteBinaryTree_IsCompleteLarge(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  // Создаем полное дерево высоты 2
  //        1
  //       / \
  //      2   3
  //     / \ /
  //    4  5 6
  values := []int{1, 2, 3, 4, 5, 6}
  for _, v := range values {
    tree.Insert(v)
  }
  
  if !tree.IsComplete() {
    t.Errorf("Большое полное дерево должно быть полным")
  }
}

func TestCompleteBinaryTree_PrintEmpty(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  tree.Print()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  
  // Print пустого дерева ничего не выводит
  if len(out) > 0 {
    t.Errorf("Print пустого дерева не должен ничего выводить")
  }
}

func TestCompleteBinaryTree_PrintSingle(t *testing.T) {
  tree := NewCompleteBinaryTree()
  tree.Insert(42)
  
  old := os.Stdout
  r, w, _ := os.Pipe()
  os.Stdout = w
  
  tree.Print()
  
  w.Close()
  os.Stdout = old
  
  out, _ := io.ReadAll(r)
  output := string(out)
  
  if !strings.Contains(output, "42") {
    t.Errorf("Вывод должен содержать значение 42")
  }
}
func TestCompleteBinaryTree_Clear(t *testing.T) {
  tree := NewCompleteBinaryTree()
  
  // Добавляем элементы
  tree.Insert(1)
  tree.Insert(2)
  tree.Insert(3)
  
  // Очищаем дерево
  tree.clear()
  
  // Проверяем, что дерево пустое
  if tree.root != nil {
    t.Errorf("Корень должен быть nil после очистки")
  }
  
  // Проверяем поиск на очищенном дереве
  if tree.Search(1) {
    t.Errorf("Поиск должен возвращать false после очистки")
  }
  
  // Проверяем IsComplete на очищенном дереве
  if !tree.IsComplete() {
    t.Errorf("Очищенное дерево должно быть полным")
  }
}