#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define ARRAY_SIZE 20
#define MAX_VALUE 50
#define NUM_OPTIONS 11


void clear_screen() {
    printf("\033[2J\033[H");
}

void sleep_ms(int milliseconds) {
    usleep(milliseconds * 1000);
}

int getch() {
    struct termios old_tio, new_tio;
    int ch;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return ch;
}

void print_array(int arr[], int size, int highlight1, int highlight2) {
    for (int i = 0; i < size; i++) {
        if (i == highlight1 || i == highlight2)
            printf("\033[0;31m"); // Set text color to red
        for (int j = 0; j < arr[i]; j++) {
            printf("%c", 219);  
        }
        printf("%d ", arr[i]);
        if (i == highlight1 || i == highlight2)
            printf("\033[0m"); // Reset text color
        printf("\n");
    }
}

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            clear_screen();
            print_array(arr, size, j, j + 1);
            sleep(100);  

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int size) {
    int i, j, min_idx;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            clear_screen();
            print_array(arr, size, min_idx, j);
            sleep(100);  

            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

void insertion_sort(int arr[], int size) {
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            clear_screen();
            print_array(arr, size, j, i);
            sleep(100); 

            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        clear_screen();
        print_array(arr, ARRAY_SIZE, l + i, m + 1 + j);
        sleep(100);  

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort_recursive(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort_recursive(arr, l, m);
        merge_sort_recursive(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void merge_sort(int arr[], int size) {
    merge_sort_recursive(arr, 0, size - 1);
}

void initialize_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % MAX_VALUE + 1;
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        clear_screen();
        print_array(arr, ARRAY_SIZE, i + 1, j);
        sleep(100);  

        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort_recursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int size) {
    quick_sort_recursive(arr, 0, size - 1);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        clear_screen();
        print_array(arr, ARRAY_SIZE, i, largest);
        sleep(100);  
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        clear_screen();
        print_array(arr, ARRAY_SIZE, 0, i);
        sleep(100);  
        heapify(arr, i, 0);
    }
}

void shell_sort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                clear_screen();
                print_array(arr, size, j, j - gap);
                sleep(100);
            }
            arr[j] = temp;
        }
    }
}

void comb_sort(int arr[], int size) {
    int gap = size;
    float shrink = 1.3;
    int sorted = 0;

    while (!sorted) {
        gap = (int)((float)gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = 1;
        }

        for (int i = 0; i + gap < size; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                sorted = 0;
                clear_screen();
                print_array(arr, size, i, i + gap);
                sleep(100);
            }
        }
    }
}

void gnome_sort(int arr[], int size) {
    int index = 0;

    while (index < size) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            swap(&arr[index], &arr[index - 1]);
            index--;
            clear_screen();
            print_array(arr, size, index, index + 1);
            sleep(100);
        }
    }
}

void cocktail_shaker_sort(int arr[], int size) {
    int swapped = 1;
    int start = 0;
    int end = size - 1;

    while (swapped) {
        swapped = 0;

        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
                clear_screen();
                print_array(arr, size, i, i + 1);
                sleep(100);
            }
        }

        if (!swapped)
            break;

        swapped = 0;
        end--;

        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
                clear_screen();
                print_array(arr, size, i, i + 1);
                sleep(100);
            }
        }

        start++;
    }
}

void display_menu(int highlight_pos) {
    printf("AlgoTerm - Terminal Algorithm Visualizer\n");
    printf("--------------------\n");

    const char* options[] = { "1. Bubble Sort", "2. Selection Sort", "3. Insertion Sort",
                              "4. Merge Sort", "5. Quick Sort", "6. Heap Sort",
                              "7. Shell Sort", "8. Comb Sort", "9. Gnome Sort",
                              "10. Cocktail Shaker Sort", "11. Exit" };

    for (int i = 0; i < NUM_OPTIONS; i++) {
        if (i == highlight_pos) {
            printf("\033[7m"); // Invert colors for highlighting
        }
        printf("%s\n", options[i]);
        if (i == highlight_pos) {
            printf("\033[0m"); // Reset colors
        }
    }

    printf("\nUse arrow keys to navigate and Enter to select, or type the number");
}

int get_user_choice() {
    int highlight_pos = 0;
    char input[3] = { 0 }; 
    int input_pos = 0;
    int ch;

    while (1) {
        clear_screen();
        display_menu(highlight_pos);

        ch = getch();
        if (ch == 27) {  // ESC character
            ch = getch();
            if (ch == 91) {  // [ character
                ch = getch();
                switch (ch) {
                case 65:  // Up arrow
                    highlight_pos = (highlight_pos - 1 + NUM_OPTIONS) % NUM_OPTIONS;
                    input_pos = 0;
                    memset(input, 0, sizeof(input));
                    break;
                case 66:  // Down arrow
                    highlight_pos = (highlight_pos + 1) % NUM_OPTIONS;
                    input_pos = 0;
                    memset(input, 0, sizeof(input));
                    break;
                }
            }
        }
        else if (ch == 10) {  // Enter key
            if (input_pos > 0) {
                int choice = atoi(input);
                if (choice > 0 && choice <= NUM_OPTIONS) {
                    return choice;
                }
            }
            else {
                return highlight_pos + 1;
            }
        }
        else if (ch >= '0' && ch <= '9' && input_pos < 2) {
            input[input_pos++] = ch;
            input[input_pos] = '\0';
            int choice = atoi(input);
            if (choice > 0 && choice <= NUM_OPTIONS) {
                highlight_pos = choice - 1;
            }
        }
        else if (ch == 127 && input_pos > 0) {  // Backspace
            input[--input_pos] = '\0';
            if (input_pos == 0) {
                highlight_pos = 0;
            }
            else {
                int choice = atoi(input);
                if (choice > 0 && choice <= NUM_OPTIONS) {
                    highlight_pos = choice - 1;
                }
            }
        }
    }
}


double run_algorithm(int choice, int arr[], int size) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    switch (choice) {
    case 1:
        printf("Running Bubble Sort...\n");
        sleep_ms(1000);
        bubble_sort(arr, size);
        break;
    case 2:
        printf("Running Selection Sort...\n");
        sleep(1000);
        selection_sort(arr, size);
        break;
    case 3:
        printf("Running Insertion Sort...\n");
        sleep(1000);
        insertion_sort(arr, size);
        break;
    case 4:
        printf("Running Merge Sort...\n");
        sleep(1000);
        merge_sort(arr, size);
        break;
    case 5:
        printf("Running Quick Sort...\n");
        sleep(1000);
        quick_sort(arr, size);
        break;
    case 6:
        printf("Running Heap Sort...\n");
        sleep(1000);
        heap_sort(arr, size);
        break;
    case 7:
        printf("Running Shell Sort...\n");
        sleep(1000);
        shell_sort(arr, size);
        break;
    case 8:
        printf("Running Comb Sort...\n");
        sleep(1000);
        comb_sort(arr, size);
        break;
    case 9:
        printf("Running Gnome Sort...\n");
        sleep(1000);
        gnome_sort(arr, size);
        break;
    case 10:
        printf("Running Cocktail Shaker Sort...\n");
        sleep(1000);
        cocktail_shaker_sort(arr, size);
        break;
    default:
        printf("Invalid choice or not implemented yet.\n");
        sleep_ms(1000);
        return 0;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main() {
    int arr[ARRAY_SIZE];
    int choice;
    double execution_time;
    srand((unsigned int)time(NULL));

    do {
        choice = get_user_choice();

        if (choice != 11) {  
            clear_screen();
            initialize_array(arr, ARRAY_SIZE);

            printf("Original array:\n");
            print_array(arr, ARRAY_SIZE, -1, -1);
            sleep_ms(2000);

            execution_time = run_algorithm(choice, arr, ARRAY_SIZE);

            printf("Sorted array:\n");
            print_array(arr, ARRAY_SIZE, -1, -1);

            printf("\nExecution time: %.2f seconds\n", execution_time);
            printf("\nPress any key to continue...");
            getch();
        }
    } while (choice != 11);

    clear_screen();
    printf("\n\n");
    printf("Thank you for using AlgoTerm!\n");
    printf("\nPress any key to exit...");
    getch();
    return 0;
}