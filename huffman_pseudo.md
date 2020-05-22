## Huffman's Algorithm Pseudo Code

### Get Frequency of Characters into Priority Queue
This was covered mostly in pa1, but we need to put all the characters and their frequency into a minimum priority queue.
```rust
    let frequency_table = frequency_table(input);
    let letter_priority = MinHeap<BinTree>::new();
    for (character, frequency) in frequency_table {
        letter_priority
            .push(
                BinTree::new(character, frequency, None, None)
                );
    }
```
Once the MinHeap is created successfully, we need to start merging the trees together to make the Huffman Tree used for encoding the input.
### 1. Build the Huffman tree from Priority Queue
```rust
    while letter_priority.len()  > 1 {
        let left = letter_priority.pop();
        let right = letter_priority.pop();
        let merged_node = BinTree::new(left.key + right.key,
         left.frequency + right.frequency, left, right);
        letter_priority.push(merged_node);
    }
```
### 2. Data Structures Used in Algorithm
The data structures that are used in the above pseudo code is a min heap, which is used to get elements with the smallest frequency, and a binary tree to store the Huffman tree that is built by the algorithm. A map was used in the first part to count the frequency of each character.
```rust
    struct MinHeap<T> {
        data: vector<T>
    }

    private MinHeap::heapify(self, smallest: int) {
        let temp = smallest;
        let left = 2 * smallest + 1;
        let right = 2 * smallest + 2;
        if left < self.data.len() && self.data[left] < self.data[smallest] {
            smallest = left;
        }
        if right < self.data.len() && self.data[right] < self.data[smallest] {
            smallest = right;
        }
        if smallest != temp {
            self.data.swap(smallest, temp);
            self.heapify(smallest);
        }
    }

    MinHeap::push(element) {
        self.data.push(element);
        self.heapify(self.data.len() / 2);
    }

    MinHeap::pop() -> element {
        let top = self.data[0];
        let self.data[0] = self.data.pop();
        self.heapify(0);
    }

    struct BinHeap {
        key,
        value,
        left,
        right
    }
```
