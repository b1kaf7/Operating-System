#include <stdio.h>
#include <stdbool.h>

void fifo(int pages[], int n, int capacity)
{
   int page_faults = 0;
   int frame[capacity];
   int frame_index = 0;

   for (int i = 0; i < n; i++)
   {
      bool page_found = false;

      // Check if page is already in the frame
      for (int j = 0; j < capacity; j++)
      {
         if (frame[j] == pages[i])
         {
            page_found = true;
            break;
         }
      }

      // If page is not found, replace the oldest page (FIFO)
      if (!page_found)
      {
         frame[frame_index] = pages[i];
         frame_index = (frame_index + 1) % capacity;
         page_faults++;
      }

      // Print current frame state
      printf("Page %d: [", pages[i]);
      for (int j = 0; j < capacity; j++)
      {
         if (frame[j] == -1)
         {
            printf(" - ");
         }
         else
         {
            printf(" %d ", frame[j]);
         }
      }
      printf("] %s\n", page_found ? "(Page found in frame)" : "(Page fault)");
   }

   printf("\nTotal Page Faults: %d\n", page_faults);
}

int main()
{
   int n, capacity;

   printf("Enter number of pages: ");
   scanf("%d", &n);

   int pages[n];

   printf("Enter page reference string:\n");
   for (int i = 0; i < n; i++)
   {
      scanf("%d", &pages[i]);
   }

   printf("Enter capacity of frames: ");
   scanf("%d", &capacity);

   fifo(pages, n, capacity);

   return 0;
}
