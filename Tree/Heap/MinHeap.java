import java.util.Scanner;

class MinHeap {
    private int[] heap;
    private int size;

    public MinHeap(int capacity) {
        heap = new int[capacity];
        size = 0;
    }

    public void insert(int data) {
        if (size == heap.length) {
            throw new RuntimeException("Heap overflow!");
        }

        heap[size++] = data;
        int i = size - 1;

        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            swap(heap, i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    public void display() {
        for (int i = 0; i < size; i++) {
            System.out.print(heap[i]);
            if (i < size - 1){
                System.out.print(",");
            }
        }
    }

    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String input = scanner.nextLine();

        String[] numbersStr = input.split(",");
        int[] numbers = new int[numbersStr.length];

        for (int i = 0; i < numbersStr.length; i++) {
            numbers[i] = Integer.parseInt(numbersStr[i]);
        }

        MinHeap heap = new MinHeap(numbers.length);
        for (int num : numbers) {
            heap.insert(num);
        }

        heap.display();
    }
}


/*  Reza Asadi (Github : RezaGooner)
	1403/03/02 ~ 2024/05/22
*/
