package classes

import "fmt"

// =======================
// constants
// =======================

const openTableSize = 10 // аналог OPEN_TABLE_SIZE

// =======================
// private entry
// =======================

type openEntry struct {
  key   string
  value string
  used  bool
}

// =======================
// HashTableOpen (PUBLIC)
// =======================

type HashTableOpen struct {
  table [openTableSize]openEntry // private
}

// =======================
// Constructor
// =======================

func NewHashTableOpen() *HashTableOpen {
  ht := &HashTableOpen{}
  for i := 0; i < openTableSize; i++ {
    ht.table[i] = openEntry{
      key:   "",
      value: "",
      used:  false,
    }
  }
  return ht
}

// =======================
// private hash function
// =======================

func (ht *HashTableOpen) hashFun(key string) int {
  hash := 0
  for _, ch := range key {
    hash += int(ch)
  }
  return hash % openTableSize
}

// =======================
// Public methods
// =======================

func (ht *HashTableOpen) Insert(value, key string) bool {
  if key == "" {
    return false
  }

  h := ht.hashFun(key)

  for i := 0; i < openTableSize; i++ {
    idx := (h + i) % openTableSize

    if !ht.table[idx].used {
      ht.table[idx] = openEntry{
        key:   key,
        value: value,
        used:  true,
      }
      return true
    }

    if ht.table[idx].key == key {
      return false
    }
  }
  return false
}

func (ht *HashTableOpen) Get(key string) string {
  h := ht.hashFun(key)

  for i := 0; i < openTableSize; i++ {
    idx := (h + i) % openTableSize

    if !ht.table[idx].used {
      return ""
    }

    if ht.table[idx].key == key {
      return ht.table[idx].value
    }
  }
  return ""
}

func (ht *HashTableOpen) Contains(key string) bool {
  h := ht.hashFun(key)

  for i := 0; i < openTableSize; i++ {
    idx := (h + i) % openTableSize

    if !ht.table[idx].used {
      return false
    }

    if ht.table[idx].key == key {
      return true
    }
  }
  return false
}

func (ht *HashTableOpen) Remove(key string) bool {
  h := ht.hashFun(key)

  for i := 0; i < openTableSize; i++ {
    idx := (h + i) % openTableSize

    if !ht.table[idx].used {
      return false
    }

    if ht.table[idx].key == key {
      ht.table[idx] = openEntry{
        key:   "",
        value: "",
        used:  false,
      }
      return true
    }
  }
  return false
}

func (ht *HashTableOpen) PrintTable() {
  fmt.Println("Хэш-таблица (ключ -> значение):")
  for i := 0; i < openTableSize; i++ {
    fmt.Print(i, ": ")
    if ht.table[i].used {
      fmt.Printf("'%s' -> '%s'", ht.table[i].key, ht.table[i].value)
    } else {
      fmt.Print("-")
    }
    fmt.Println()
  }
}

// =======================
// Debug (для тестов)
// =======================

func (ht *HashTableOpen) DebugIndex(key string) int {
  return ht.hashFun(key)
}