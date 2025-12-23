package classes

import (
  "fmt"
	"io"
	"bufio"
	"encoding/binary"
	"os"
	"strconv"
	"strings"
)

type Serializable interface {
	SaveText(filename string) error
	LoadText(filename string) error
	SaveBinary(filename string) error
	LoadBinary(filename string) error
}


func (fl *ForwardList) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Записываем заголовок
	fmt.Fprintf(writer, "ForwardList v1.0\n")
	fmt.Fprintf(writer, "size:%d\n", fl.size)
	fmt.Fprintln(writer, "data:")
	
	// Записываем элементы в порядке от головы к хвосту
	current := fl.head
	for current != nil {
		fmt.Fprintf(writer, "%s\n", current.data)
		current = current.next
	}
	
	return writer.Flush()
}

func (fl *ForwardList) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий список
	fl.head = nil
	fl.size = 0
	
	scanner := bufio.NewScanner(file)
	readingData := false
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingData {
			if strings.HasPrefix(line, "size:") {
				// Просто пропускаем, размер восстановится сам
				continue
			} else if line == "data:" {
				readingData = true
			}
		} else {
			// Добавляем в хвост (сохраняем порядок)
			fl.AddTail(line)
		}
	}
	
	return scanner.Err()
}

func (fl *ForwardList) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Записываем количество элементов
	err = binary.Write(file, binary.LittleEndian, int32(fl.size))
	if err != nil {
		return err
	}

	// Записываем элементы в порядке от головы к хвосту
	current := fl.head
	for current != nil {
		// Длина строки
		strBytes := []byte(current.data)
		err = binary.Write(file, binary.LittleEndian, int32(len(strBytes)))
		if err != nil {
			return err
		}
		
		// Сама строка
		_, err = file.Write(strBytes)
		if err != nil {
			return err
		}
		
		current = current.next
	}
	
	return nil
}

func (fl *ForwardList) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий список
	fl.head = nil
	fl.size = 0
	
	// Читаем количество элементов
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем элементы и добавляем в хвост
	for i := 0; i < int(count); i++ {
		// Длина строки
		var strLen int32
		err = binary.Read(file, binary.LittleEndian, &strLen)
		if err != nil {
			return err
		}

		// Сама строка
		strBytes := make([]byte, strLen)
		_, err = io.ReadFull(file, strBytes)
		if err != nil {
			return err
		}

		fl.AddTail(string(strBytes))
	}
	
	return nil
}

//------------------------------------

func (dl *DoublyList) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Записываем заголовок
	fmt.Fprintf(writer, "DoublyList v1.0\n")
	fmt.Fprintf(writer, "size:%d\n", dl.size)
	fmt.Fprintln(writer, "data:")
	
	// Записываем элементы в прямом порядке
	current := dl.head
	for current != nil {
		fmt.Fprintf(writer, "%s\n", current.data)
		current = current.next
	}
	
	return writer.Flush()
}

func (dl *DoublyList) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий список
	dl.head = nil
	dl.tail = nil
	dl.size = 0
	
	scanner := bufio.NewScanner(file)
	readingData := false
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingData {
			if line == "data:" {
				readingData = true
			}
		} else {
			// Добавляем в хвост (сохраняем порядок и восстанавливаем связи)
			dl.AddTail(line)
		}
	}
	
	return scanner.Err()
}

func (dl *DoublyList) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Записываем количество элементов
	err = binary.Write(file, binary.LittleEndian, int32(dl.size))
	if err != nil {
		return err
	}

	// Записываем элементы в прямом порядке
	current := dl.head
	for current != nil {
		// Длина строки
		strBytes := []byte(current.data)
		err = binary.Write(file, binary.LittleEndian, int32(len(strBytes)))
		if err != nil {
			return err
		}
		
		// Сама строка
		_, err = file.Write(strBytes)
		if err != nil {
			return err
		}
		
		current = current.next
	}
	
	return nil
}

func (dl *DoublyList) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий список
	dl.head = nil
	dl.tail = nil
	dl.size = 0
	
	// Читаем количество элементов
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем элементы и добавляем в хвост
	for i := 0; i < int(count); i++ {
		// Длина строки
		var strLen int32
		err = binary.Read(file, binary.LittleEndian, &strLen)
		if err != nil {
			return err
		}

		// Сама строка
		strBytes := make([]byte, strLen)
		_, err = io.ReadFull(file, strBytes)
		if err != nil {
			return err
		}

		dl.AddTail(string(strBytes))
	}
	
	return nil
}

//------------------------------------

func (a *Array) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Записываем размер
	fmt.Fprintf(writer, "size:%d\n", a.size)
	fmt.Fprintf(writer, "capacity:%d\n", a.capacity)
	fmt.Fprintln(writer, "data:")
	
	// Записываем данные
	for i := 0; i < a.size; i++ {
		fmt.Fprintf(writer, "%s\n", a.data[i])
	}
	
	return writer.Flush()
}

//текстовая десериализация
func (a *Array) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий массив
	a.size = 0
	
	scanner := bufio.NewScanner(file)
	readingData := false
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingData {
			if strings.HasPrefix(line, "size:") {
				sizeStr := strings.TrimPrefix(line, "size:")
				size, _ := strconv.Atoi(sizeStr)
				// Просто запоминаем, не используем пока
				_ = size
			} else if strings.HasPrefix(line, "capacity:") {
				capStr := strings.TrimPrefix(line, "capacity:")
				capacity, _ := strconv.Atoi(capStr)
				if capacity > a.capacity {
					a.resize(capacity)
				}
			} else if line == "data:" {
				readingData = true
			}
		} else {
			a.PushBack(line)
		}
	}
	
	return scanner.Err()
}

// бинарная сериализация
func (a *Array) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Записываем размер
	err = binary.Write(file, binary.LittleEndian, int32(a.size))
	if err != nil {
		return err
	}

	// Записываем capacity
	err = binary.Write(file, binary.LittleEndian, int32(a.capacity))
	if err != nil {
		return err
	}

	// Записываем каждую строку
	for i := 0; i < a.size; i++ {
		// Длина строки
		strBytes := []byte(a.data[i])
		err = binary.Write(file, binary.LittleEndian, int32(len(strBytes)))
		if err != nil {
			return err
		}
		
		// Сама строка
		_, err = file.Write(strBytes)
		if err != nil {
			return err
		}
	}
	
	return nil
}

// бинарная десериализация
func (a *Array) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Читаем размер
	var size int32
	err = binary.Read(file, binary.LittleEndian, &size)
	if err != nil {
		return err
	}

	// Читаем capacity
	var capacity int32
	err = binary.Read(file, binary.LittleEndian, &capacity)
	if err != nil {
		return err
	}

	// Очищаем и готовим массив
	a.size = 0
	if int(capacity) > a.capacity {
		a.resize(int(capacity))
	}

	// Читаем строки
	for i := 0; i < int(size); i++ {
		// Длина строки
		var strLen int32
		err = binary.Read(file, binary.LittleEndian, &strLen)
		if err != nil {
			return err
		}

		// Сама строка
		strBytes := make([]byte, strLen)
		_, err = io.ReadFull(file, strBytes)
		if err != nil {
			return err
		}

		a.PushBack(string(strBytes))
	}
	
	return nil
}

//------------------------------------

func (q *Queue) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Собираем все элементы
	elements := []string{}
	cur := q.front
	for cur != nil {
		elements = append(elements, cur.data)
		cur = cur.next
	}
	
	// Записываем количество
	fmt.Fprintf(writer, "count:%d\n", len(elements))
	fmt.Fprintln(writer, "data:")
	
	// Записываем данные
	for _, elem := range elements {
		fmt.Fprintf(writer, "%s\n", elem)
	}
	
	return writer.Flush()
}

func (q *Queue) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущую очередь
	q.front = nil
	q.rear = nil
	
	scanner := bufio.NewScanner(file)
	readingData := false
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingData {
			if strings.HasPrefix(line, "count:") {
				// Просто пропускаем
				continue
			} else if line == "data:" {
				readingData = true
			}
		} else {
			q.Push(line)
		}
	}
	
	return scanner.Err()
}

func (q *Queue) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Собираем все элементы
	elements := []string{}
	cur := q.front
	for cur != nil {
		elements = append(elements, cur.data)
		cur = cur.next
	}
	
	// Записываем количество
	err = binary.Write(file, binary.LittleEndian, int32(len(elements)))
	if err != nil {
		return err
	}

	// Записываем каждую строку
	for _, elem := range elements {
		strBytes := []byte(elem)
		
		// Длина строки
		err = binary.Write(file, binary.LittleEndian, int32(len(strBytes)))
		if err != nil {
			return err
		}
		
		// Сама строка
		_, err = file.Write(strBytes)
		if err != nil {
			return err
		}
	}
	
	return nil
}

func (q *Queue) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущую очередь
	q.front = nil
	q.rear = nil
	
	// Читаем количество
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем строки
	for i := 0; i < int(count); i++ {
		// Длина строки
		var strLen int32
		err = binary.Read(file, binary.LittleEndian, &strLen)
		if err != nil {
			return err
		}

		// Сама строка
		strBytes := make([]byte, strLen)
		_, err = io.ReadFull(file, strBytes)
		if err != nil {
			return err
		}

		q.Push(string(strBytes))
	}
	
	return nil
}

//------------------------------------

func (s *Stack) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Собираем все элементы (снизу вверх)
	elements := []string{}
	cur := s.head
	for cur != nil {
		// Добавляем в начало, чтобы сохранить порядок
		elements = append([]string{cur.data}, elements...)
		cur = cur.next
	}
	
	// Записываем количество
	fmt.Fprintf(writer, "count:%d\n", len(elements))
	fmt.Fprintln(writer, "data:")
	
	// Записываем данные
	for _, elem := range elements {
		fmt.Fprintf(writer, "%s\n", elem)
	}
	
	return writer.Flush()
}

func (s *Stack) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий стек
	s.Clear()
	
	scanner := bufio.NewScanner(file)
	readingData := false
	temp := []string{}
	
	// Сначала читаем все элементы
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingData {
			if line == "data:" {
				readingData = true
			}
		} else {
			temp = append(temp, line)
		}
	}
	
	// Загружаем в обратном порядке (чтобы верх остался верхом)
	for i := len(temp) - 1; i >= 0; i-- {
		s.Push(temp[i])
	}
	return scanner.Err()
}

func (s *Stack) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Собираем все элементы (снизу вверх)
	elements := []string{}
	cur := s.head
	for cur != nil {
		elements = append([]string{cur.data}, elements...)
		cur = cur.next
	}
	
	// Записываем количество
	err = binary.Write(file, binary.LittleEndian, int32(len(elements)))
	if err != nil {
		return err
	}

	// Записываем каждую строку
	for _, elem := range elements {
		strBytes := []byte(elem)
		
		// Длина строки
		err = binary.Write(file, binary.LittleEndian, int32(len(strBytes)))
		if err != nil {
			return err
		}
		
		// Сама строка
		_, err = file.Write(strBytes)
		if err != nil {
			return err
		}
	}
	
	return nil
}


func (s *Stack) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем текущий стек
	s.Clear()
	
	// Читаем количество
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем строки во временный массив
	temp := make([]string, count)
	for i := 0; i < int(count); i++ {
		// Длина строки
		var strLen int32
		err = binary.Read(file, binary.LittleEndian, &strLen)
		if err != nil {
			return err
		}

		// Сама строка
		strBytes := make([]byte, strLen)
		_, err = io.ReadFull(file, strBytes)
		if err != nil {
			return err
		}

		temp[i] = string(strBytes)
	}
	
	// Загружаем в обратном порядке
	for i := len(temp) - 1; i >= 0; i-- {
		s.Push(temp[i])
	}
	
	return nil
}

//------------------------------------

func (ht *HashTableOpen) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Записываем размер таблицы
	fmt.Fprintf(writer, "tablesize:%d\n", openTableSize)
	fmt.Fprintln(writer, "entries:")
	
	// Записываем только использованные ячейки
	count := 0
	for i := 0; i < openTableSize; i++ {
		if ht.table[i].used {
			fmt.Fprintf(writer, "%s:%s\n", ht.table[i].key, ht.table[i].value)
			count++
		}
	}
	
	// Перезаписываем количество в начале
	writer.Flush()
	
	// Нужно переоткрыть файл или использовать другой подход
	// Для простоты просто записываем count
	file2, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file2.Close()
	
	writer2 := bufio.NewWriter(file2)
	fmt.Fprintf(writer2, "tablesize:%d\n", openTableSize)
	fmt.Fprintf(writer2, "count:%d\n", count)
	fmt.Fprintln(writer2, "entries:")
	
	for i := 0; i < openTableSize; i++ {
		if ht.table[i].used {
			fmt.Fprintf(writer2, "%s:%s\n", ht.table[i].key, ht.table[i].value)
		}
	}
	
	return writer2.Flush()
}

func (ht *HashTableOpen) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем таблицу
	for i := 0; i < openTableSize; i++ {
		ht.table[i] = openEntry{used: false}
	}
	
	scanner := bufio.NewScanner(file)
	readingEntries := false
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingEntries {
			if strings.HasPrefix(line, "entries:") {
				readingEntries = true
			}
		} else {
			// Формат: ключ:значение
			parts := strings.SplitN(line, ":", 2)
			if len(parts) == 2 {
				ht.Insert(parts[1], parts[0])
			}
		}
	}
	
	return scanner.Err()
}

func (ht *HashTableOpen) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Считаем количество использованных ячеек
	count := 0
	for i := 0; i < openTableSize; i++ {
		if ht.table[i].used {
			count++
		}
	}
	
	// Записываем количество
	err = binary.Write(file, binary.LittleEndian, int32(count))
	if err != nil {
		return err
	}

	// Записываем каждую пару ключ-значение
	for i := 0; i < openTableSize; i++ {
		if ht.table[i].used {
			// Ключ
			keyBytes := []byte(ht.table[i].key)
			err = binary.Write(file, binary.LittleEndian, int32(len(keyBytes)))
			if err != nil {
				return err
			}
			_, err = file.Write(keyBytes)
			if err != nil {
				return err
			}
			
			// Значение
			valueBytes := []byte(ht.table[i].value)
			err = binary.Write(file, binary.LittleEndian, int32(len(valueBytes)))
			if err != nil {
				return err
			}
			_, err = file.Write(valueBytes)
			if err != nil {
				return err
			}
		}
	}
	
	return nil
}


func (ht *HashTableOpen) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем таблицу
	for i := 0; i < openTableSize; i++ {
		ht.table[i] = openEntry{used: false}
	}
	
	// Читаем количество записей
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем пары ключ-значение
	for i := 0; i < int(count); i++ {
		// Ключ
		var keyLen int32
		err = binary.Read(file, binary.LittleEndian, &keyLen)
		if err != nil {
			return err
		}
		keyBytes := make([]byte, keyLen)
		_, err = io.ReadFull(file, keyBytes)
		if err != nil {
			return err
		}
		key := string(keyBytes)
		
		// Значение
		var valueLen int32
		err = binary.Read(file, binary.LittleEndian, &valueLen)
		if err != nil {
			return err
		}
		valueBytes := make([]byte, valueLen)
		_, err = io.ReadFull(file, valueBytes)
		if err != nil {
			return err
		}
		value := string(valueBytes)
		
		ht.Insert(value, key)
	}
	
	return nil
}

//------------------------------------

func (ht *ChainHashTable) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	// Собираем все пары ключ-значение
	pairs := []string{}
	for i := 0; i < chainTableSize; i++ {
		curr := ht.table[i]
		for curr != nil {
			pairs = append(pairs, fmt.Sprintf("%s:%s", curr.key, curr.value))
			curr = curr.next
		}
	}
	
	// Записываем количество
	fmt.Fprintf(writer, "count:%d\n", len(pairs))
	fmt.Fprintln(writer, "entries:")
	
	// Записываем данные
	for _, pair := range pairs {
		fmt.Fprintf(writer, "%s\n", pair)
	}
	
	return writer.Flush()
}

func (ht *ChainHashTable) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем таблицу
	for i := 0; i < chainTableSize; i++ {
		ht.table[i] = nil
	}
	
	scanner := bufio.NewScanner(file)
	readingEntries := false
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingEntries {
			if strings.HasPrefix(line, "entries:") {
				readingEntries = true
			}
		} else {
			// Формат: ключ:значение
			parts := strings.SplitN(line, ":", 2)
			if len(parts) == 2 {
				ht.Insert(parts[0], parts[1])
			}
		}
	}
	
	return scanner.Err()
}

func (ht *ChainHashTable) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Собираем все пары ключ-значение
	keys := []string{}
	values := []string{}
	
	for i := 0; i < chainTableSize; i++ {
		curr := ht.table[i]
		for curr != nil {
			keys = append(keys, curr.key)
			values = append(values, curr.value)
			curr = curr.next
		}
	}
	
	// Записываем количество
	err = binary.Write(file, binary.LittleEndian, int32(len(keys)))
	if err != nil {
		return err
	}

	// Записываем пары
	for i := 0; i < len(keys); i++ {
		// Ключ
		keyBytes := []byte(keys[i])
		err = binary.Write(file, binary.LittleEndian, int32(len(keyBytes)))
		if err != nil {
			return err
		}
		_, err = file.Write(keyBytes)
		if err != nil {
			return err
		}
		
		// Значение
		valueBytes := []byte(values[i])
		err = binary.Write(file, binary.LittleEndian, int32(len(valueBytes)))
		if err != nil {
			return err
		}
		_, err = file.Write(valueBytes)
		if err != nil {
			return err
		}
	}
	
	return nil
}

func (ht *ChainHashTable) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем таблицу
	for i := 0; i < chainTableSize; i++ {
		ht.table[i] = nil
	}
	
	// Читаем количество записей
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем пары ключ-значение
	for i := 0; i < int(count); i++ {
		// Ключ
		var keyLen int32
		err = binary.Read(file, binary.LittleEndian, &keyLen)
		if err != nil {
			return err
		}
		keyBytes := make([]byte, keyLen)
		_, err = io.ReadFull(file, keyBytes)
		if err != nil {
			return err
		}
		key := string(keyBytes)
		
		// Значение
		var valueLen int32
		err = binary.Read(file, binary.LittleEndian, &valueLen)
		if err != nil {
			return err
		}
		valueBytes := make([]byte, valueLen)
		_, err = io.ReadFull(file, valueBytes)
		if err != nil {
			return err
		}
		value := string(valueBytes)
		
		ht.Insert(key, value)
	}
	
	return nil
}

//------------------------------------

func (t *CompleteBinaryTree) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	
	if t.root == nil {
		fmt.Fprintln(writer, "count:0")
		fmt.Fprintln(writer, "data:")
		return writer.Flush()
	}
	
	// Обход в ширину для сохранения
	queue := list.New()
	queue.PushBack(t.root)
	
	values := []string{}
	
	for queue.Len() > 0 {
		node := queue.Remove(queue.Front()).(*treeNode)
		values = append(values, strconv.Itoa(node.data))
		
		if node.left != nil {
			queue.PushBack(node.left)
		}
		if node.right != nil {
			queue.PushBack(node.right)
		}
	}
	
	// Записываем количество
	fmt.Fprintf(writer, "count:%d\n", len(values))
	fmt.Fprintln(writer, "data:")
	
	// Записываем данные
	for _, val := range values {
		fmt.Fprintf(writer, "%s\n", val)
	}
	
	return writer.Flush()
}

func (t *CompleteBinaryTree) LoadText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем дерево
	t.clear()
	
	scanner := bufio.NewScanner(file)
	readingData := false
	values := []int{}
	
	for scanner.Scan() {
		line := scanner.Text()
		
		if !readingData {
			if line == "data:" {
				readingData = true
			}
		} else {
			val, err := strconv.Atoi(line)
			if err == nil {
				values = append(values, val)
			}
		}
	}
	
	// Восстанавливаем дерево
	for _, val := range values {
		t.Insert(val)
	}
	
	return scanner.Err()
}

func (t *CompleteBinaryTree) SaveBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if t.root == nil {
		// Записываем 0 как количество элементов
		err = binary.Write(file, binary.LittleEndian, int32(0))
		return err
	}
	
	// Обход в ширину
	queue := list.New()
	queue.PushBack(t.root)
	
	values := []int32{}
	
	for queue.Len() > 0 {
		node := queue.Remove(queue.Front()).(*treeNode)
		values = append(values, int32(node.data))
		
		if node.left != nil {
			queue.PushBack(node.left)
		}
		if node.right != nil {
			queue.PushBack(node.right)
		}
	}
	
	// Записываем количество
	err = binary.Write(file, binary.LittleEndian, int32(len(values)))
	if err != nil {
		return err
	}

	// Записываем значения
	for _, val := range values {
		err = binary.Write(file, binary.LittleEndian, val)
		if err != nil {
			return err
		}
	}
	
	return nil
}

func (t *CompleteBinaryTree) LoadBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Очищаем дерево
	t.clear()
	
	// Читаем количество
	var count int32
	err = binary.Read(file, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем значения
	values := make([]int, count)
	for i := 0; i < int(count); i++ {
		var val int32
		err = binary.Read(file, binary.LittleEndian, &val)
		if err != nil {
			return err
		}
		values[i] = int(val)
	}
	
	// Восстанавливаем дерево
	for _, val := range values {
		t.Insert(val)
	}
	
	return nil
}
