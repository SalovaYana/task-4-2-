// таск 4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int value;
	struct node* next;
};

typedef struct node spisok;

void first_5(spisok *head)
{
	    
	    spisok* tmp = head ;
		
	
	for (int i = 0; i < 5; ++i)
	{    
		spisok* el = (struct node*)malloc(sizeof(spisok));

		tmp->next = el;

        el->next = NULL;
		el->value = 1 + rand()%25;
		

		tmp = tmp->next;
	}
}


void push(spisok* head, spisok *newone)
{
	newone->next=head->next;
	head->next = newone;

}

void print(spisok* head) 
{

	spisok* tmp = head;

	while (tmp->next != NULL)
	{

		printf_s("%d->", tmp->value);

		tmp = tmp->next;
	}
	printf_s("%d", tmp->value);
}


void insert_before(spisok* newone, spisok* given, spisok* previous)
{
	newone->next = given;
	previous->next = newone;
}

void insert_after(spisok* newone, spisok* given, spisok* next_el)
{
	newone->next = next_el;
	given->next = newone;
}


void insert_end(spisok* newone, spisok* head)
{
	spisok* tmp = head;

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = newone;
	newone->next = NULL;
}

void delete_first(spisok* head, spisok* first)
{
	head->next = first->next;
	free(first);
}

void delete_last(spisok* head)
{
	spisok* tmp = head;
	spisok* last;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	tmp->next = NULL;

	last = tmp->next;
	free(last);
}


void delete_given(spisok* previous, spisok* next_el)
{
	previous->next = next_el;

}

int individual(int given, spisok* head)
{
	int k = 1;
	spisok* tmp1;
	tmp1 = head->next;

	while (tmp1->next != NULL)
	{
		if (given == tmp1->value)
			k = k + 1;
		tmp1 = tmp1->next;
	}
	return (k);
}

spisok* search_for_el(int data, spisok* head, int previous)
{
	spisok* tmp = head;

	while (tmp->next != NULL)
	{
		if (previous == 0)
		{
			if (tmp->value == data)
			{
				return tmp;
			}
		}
		else if (tmp->next->value == data)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	if (tmp->value == data)
		return tmp;
	return NULL;
}

spisok* create_new_el(int data)
{
	spisok* result = (struct node*)malloc(sizeof(spisok));
	result->value = data;
	result->next = NULL;
	return result;
}

void print_menu()
{

	printf("\nWhat do you want to do?\n");
	printf("0. Exit\n");
	printf("1. Add an element\n");
	printf("2. Delete an element\n");
	printf("3. Individual task: calculate the number of times a given element occurs\n");
	printf_s("\n");

}
void print_menu_add()
{

	printf("\nWhere do you want to add the element?\n");
	printf("1.in the beginning\n");
	printf("2.before the given element\n");
	printf("3.after the given element\n");
	printf("4.to the end\n");
	printf_s("\n");

}


void print_menu_delete()
{
	printf("\nWhere do you want to delete an element from?\n");
	printf("1.from the beginning\n");
	printf("2.delete the given element\n");
	printf("3.from the end\n");
	printf_s("\n");

}



int main()
{
	srand(time(NULL));
	int choice=1;
	int choice_2;
	int val, given;
	

	spisok* head = (struct node*)malloc(sizeof(spisok));
	spisok* el = (struct node*)malloc(sizeof(spisok));

	head->value = 0;
	head->next = NULL;



	spisok* newone = (struct node*)malloc(sizeof(spisok));
	newone->next = NULL;

	first_5(head);
	print(head);


	while (choice != 0)
	{
		print_menu();
	    scanf_s("%d", &choice);


		switch (choice)
		{
		case 1:
			printf_s("\nenter the value of the new element\n");
			scanf_s("%d", &val);

			newone = create_new_el(val);


			print_menu_add();
			scanf_s("%d", &choice_2);

			switch (choice_2)
			{
			case 1:

				push(head, newone);
				print(head);
				break;


			case 2:
				if (head->next == NULL)
				{
					printf_s("the list is still empty, add a new element in the beginning\n");

				}
				else
				{

					printf_s("\nwrite an element to add a new one before\n");
					scanf_s("%d", &given);

					el = search_for_el(given, head, 1);

					insert_before(newone, el->next, el);

					print(head);

				}
				
				break;

			case 3:
				if (head->next == NULL)
				{
					printf_s("\nthe list is still empty, add a new element in the beginning\n");

				}
				else
				{

					printf_s("\nwrite an element to add a new one after\n");
					scanf_s("%d", &given);

					el = search_for_el(given, head, 0);

					insert_after(newone, el, el->next);

					print(head);
				}
				break;


			case 4:
				insert_end(newone, head);

				print(head);
				break;

			}
			break;

		case 2:
			if (head->next == NULL)
			{
				printf_s("\nthe list is still empty, add a new element in the beginning\n");

			}
			else
			{

				print_menu_delete();
				scanf_s("%d", &choice_2);

				switch (choice_2)
				{
				case 1:
					delete_first(head, head->next);

					print(head);
					break;

				case 2:
					printf_s("\nwrite an element to delete\n");
					scanf_s("%d", &given);

					el = search_for_el(given, head, 1);

					delete_given(el, el->next->next);

					print(head);
					break;

				case 3:
					delete_last(head);

					print(head);
					break;

					
				}
			}
			break;
		case 3:
			printf_s("\nenter an element to count the number of its occurrences\n");
			scanf_s("%d", &val);

			printf_s("k=%d", individual(val,head));
			break;
			}

		}


	
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
