#include <stdio.h>

typedef struct
{
	int number_of_elements;
	int capacity;

	int buffer[100];
	int front;
	int rear;
}Queue;

void InitQueue(Queue *queue,int capacity)
{
	int i;
	queue->number_of_elements = 0;
	queue->capacity = capacity;
	queue->front = capacity-1;
	queue->rear = capacity-1;

	for (i = 0; i < capacity; i++)
	{
		queue->buffer[i] = 0;
	}
}

int getEmptyPosition(Queue *queue,int index)
{

	while (queue->buffer[index] != 0)
		index = (index + 1) % queue->capacity;
	return index;
}

void ShiftToRight(Queue *queue,int index,int value)
{
	int capacity = queue->capacity;
	// We find first empty position
	int j = getEmptyPosition(queue, index);

	while (j != index)
	{
		queue->buffer[j] = queue->buffer[(((j - 1) % capacity) + capacity) % capacity];
			j = (((j - 1) % capacity) + capacity) % capacity;
	}

	queue->buffer[index] = value;
}

void Insert(Queue *queue, int value)
{
	if (queue->rear+1 % (queue->capacity) == queue->front)
	{
		printf("Queue is full!\n");
	}
	else
	{
		int capacity = queue->capacity;
		int index = (queue->front+1)%capacity;

		while (value >= queue->buffer[index] && queue->buffer[index] != 0)
		{
			index = (index+1) % queue->capacity;
		}
		ShiftToRight(queue, index,value);
		queue->rear = (queue->rear + 1) % capacity;
		
		queue->number_of_elements += 1;
		}
}

int Delete(Queue *queue)
{
	if (queue->front == queue->rear)
	{
		printf("Queue is empty!\n");
	}
	else
	{
		queue->front = (queue->front + 1) % queue->capacity;
		int value = queue->buffer[queue->front];
		queue->buffer[queue->front] = 0;
		
		queue->number_of_elements -= 1;
		return value;
	}
}

void Print(Queue *queue)
{
	printf("----------------\n");
	int n = queue->capacity;
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", queue->buffer[i]);
	}
	printf("\n");
}

void CreateQueue(Queue *queue)
{
	int capacity;
	printf("Enter queue size: \n");
	scanf("%d", &capacity);
	InitQueue(queue, capacity);
}

int Get(Queue *queue)
{
	int capacity = queue->capacity;
	return queue->buffer[(queue->front + 1) % capacity];
}

int GetNumberOfElements(Queue *queue)
{
	printf("Number Of Elements: %d\n", queue->number_of_elements);
	return queue->number_of_elements;
}

int GetCapacity(Queue *queue)
{
	printf("Capacity: %d\n", queue->capacity);
	return queue->capacity;
}

void InsertElement(Queue *queue)
{
	int value;
	printf("Enter value:\n");
	scanf("%d", &value);
	Insert(queue, value);
}

void callMenu()
{
	printf("----------------\n");
	printf("1 - Create New Queue\n");
	printf("2 - Insert Element\n");
	printf("3 - Delete Element\n");
	printf("4 - Get Element\n");
	printf("5 - Get number Of Elements\n");
	printf("6 - Get Capacity\n");
	printf("----------------\n");
}

int main()
{
	Queue q;
	while (1)
	{
		callMenu();
		int operation;
		scanf("%d", &operation);
		
		switch (operation)
		{
		case 1:
			CreateQueue(&q);
			break;
		case 2:
			InsertElement(&q);
			break;
		case 3:
			Delete(&q);
			break;
		case 4:
			Get(&q);
			break;
		case 5:
			GetNumberOfElements(&q);
			break;
		case 6:
			GetCapacity(&q);
			break;
		default:
			printf("Please enter valid option!\n");
			break;
		}
		Print(&q);
	}
}