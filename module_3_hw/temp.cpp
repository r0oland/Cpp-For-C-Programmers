void PriorityQueue::PriorityQueue() {
    heap.push_back(0);
}

void PriorityQueue::push(int value) {
    heap.push_back(value);
    percolate_up(heap.size() - 1);
}

int PriorityQueue::pop() {
    int result = heap[1];
    heap[1] = heap.back();
    heap.pop_back();
    percolate_down(1);
    return result;
}

int PriorityQueue::top() {
    return heap[1];
}

int PriorityQueue::size() {
    return heap.size() - 1;
}

bool PriorityQueue::empty() {
    return heap.size() == 1;
}

void PriorityQueue::print() {
    for (int i = 1; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

void PriorityQueue::percolate_up(int index) {
    int parent = index / 2;
    if (index > 1 && heap[index] < heap[parent]) {
        int temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;
        percolate_up(parent);
    }
}

void PriorityQueue::percolate_down(int index) {
    int left = index * 2;
    int right = index * 2 + 1;
    int smallest = index;
    if (left < heap.size() && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < heap.size() && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        int temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        percolate_down(smallest);
    }
}
