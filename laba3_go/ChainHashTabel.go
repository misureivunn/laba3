package classes

// =======================
// constants
// =======================

const chainTableSize = 10 // аналог CHAIN_TABLE_SIZE

// =======================
// private node
// =======================

type chainNode struct {
  key   string
  value string
  next  *chainNode
}

// =======================
// ChainHashTable (PUBLIC)
// =======================

type ChainHashTable struct {
  table [chainTableSize]*chainNode // private
}

// =======================
// Constructor
// =======================

func NewChainHashTable() *ChainHashTable {
  ht := &ChainHashTable{}
  for i := 0; i < chainTableSize; i++ {
    ht.table[i] = nil
  }
  return ht
}

// =======================
// private hash function
// =======================

func (ht *ChainHashTable) hashFun(key string) int {
  hash := 0
  for _, ch := range key {
    hash += int(ch)
  }
  return hash % chainTableSize
}

// =======================
// Public methods
// =======================

func (ht *ChainHashTable) Contains(key string) bool {
  h := ht.hashFun(key)
  curr := ht.table[h]

  for curr != nil {
    if curr.key == key {
      return true
    }
    curr = curr.next
  }
  return false
}

func (ht *ChainHashTable) Get(key string) string {
  h := ht.hashFun(key)
  curr := ht.table[h]

  for curr != nil {
    if curr.key == key {
      return curr.value
    }
    curr = curr.next
  }
  return ""
}

func (ht *ChainHashTable) Insert(key, value string) bool {
  if ht.Contains(key) {
    return false
  }

  h := ht.hashFun(key)
  newNode := &chainNode{
    key:   key,
    value: value,
    next:  ht.table[h],
  }
  ht.table[h] = newNode
  return true
}

func (ht *ChainHashTable) Remove(key string) {
  h := ht.hashFun(key)
  curr := ht.table[h]
  var prev *chainNode = nil

  for curr != nil {
    if curr.key == key {
      if prev != nil {
        prev.next = curr.next
      } else {
        ht.table[h] = curr.next
      }
      return
    }
    prev = curr
    curr = curr.next
  }
}
