package classes

import (
  "container/list"
  "fmt"
)

// TreeNode (private)

type treeNode struct {
  data  int
  left  *treeNode
  right *treeNode
}

// CompleteBinaryTree (public)
type CompleteBinaryTree struct {
  root *treeNode // приватный корень
}

// Constructor

func NewCompleteBinaryTree() *CompleteBinaryTree {
  return &CompleteBinaryTree{root: nil}
}

func (t *CompleteBinaryTree) Insert(value int) {
  node := &treeNode{data: value}
  if t.root == nil {
    t.root = node
    return
  }

  q := list.New()
  q.PushBack(t.root)

  for q.Len() > 0 {
    cur := q.Remove(q.Front()).(*treeNode)

    if cur.left == nil {
      cur.left = node
      return
    } else {
      q.PushBack(cur.left)
    }

    if cur.right == nil {
      cur.right = node
      return
    } else {
      q.PushBack(cur.right)
    }
  }
}

func (t *CompleteBinaryTree) Search(value int) bool {
  if t.root == nil {
    return false
  }

  q := list.New()
  q.PushBack(t.root)

  for q.Len() > 0 {
    cur := q.Remove(q.Front()).(*treeNode)
    if cur.data == value {
      return true
    }
    if cur.left != nil {
      q.PushBack(cur.left)
    }
    if cur.right != nil {
      q.PushBack(cur.right)
    }
  }
  return false
}

func (t *CompleteBinaryTree) IsComplete() bool {
  if t.root == nil {
    return true
  }

  q := list.New()
  q.PushBack(t.root)
  flag := false

  for q.Len() > 0 {
    cur := q.Remove(q.Front()).(*treeNode)

    if cur.left != nil {
      if flag {
        return false
      }
      q.PushBack(cur.left)
    } else {
      flag = true
    }

    if cur.right != nil {
      if flag {
        return false
      }
      q.PushBack(cur.right)
    } else {
      flag = true
    }
  }
  return true
}

func (t *CompleteBinaryTree) Print() {
  t.printNode(t.root, 0)
}

func (t *CompleteBinaryTree) printNode(node *treeNode, indent int) {
  if node == nil {
    return
  }
  if node.right != nil {
    t.printNode(node.right, indent+4)
  }
  if indent > 0 {
    fmt.Print(fmt.Sprintf("%*s", indent, ""))
  }
  fmt.Println(node.data)
  if node.left != nil {
    t.printNode(node.left, indent+4)
  }
}

func (t *CompleteBinaryTree) clear() {
  t.clearNode(t.root)
  t.root = nil
}

func (t *CompleteBinaryTree) clearNode(node *treeNode) {
  if node == nil {
    return
  }
  t.clearNode(node.left)
  t.clearNode(node.right)
  node.left = nil
  node.right = nil
}
