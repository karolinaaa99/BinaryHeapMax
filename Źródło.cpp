#include <iostream>

using namespace std;

class Heap 
{
private:
	int* kopiec; //tablica dynamiczna przechowujaca elementy kopca
	int capacity; //maksymalny rozmiar tablicy (kopca)
	int heap_size; //liczba elementow w tablicy, czyli liczba elementow kopca
public:
	Heap(int c); //tworzy pusty kopiec o pojemności c
	Heap();	//konstruktor do testów kopca - należy utworzyć kopiec nast. zawartością: 12,9,10,7,9,5,9,2,1,3
	bool empty();  //zwraca true, jesli kopiec jest pusty, false w przeciwnym razie
	bool full(); //zwraca true, jesli kopiec jest pelny, false w przeciwnym razie
	int left(int i); //zwraca pozycję lewego syna
	int right(int i); //zwraca pozycję prawego syna
	int parent(int i);	//zwraca pozycję ojca
	int getSize();	//zwraca rozmiar kopca
	void setHeapSize(int s); //ustawia rozmiar kopca
	int get(int i);	//zwraca wartość z pozycji i
	void set(int i, int x);	//ustawia wartość x na pozycji i
	void up(int i);	//przywraca własność kopca metodą wynurzania
	void down(int i); //przywraca własność kopca metodą zatapiania
	friend ostream& operator<<(ostream& out, Heap& h); //wyswietla kopiec na ekranie
};

/* należy utworzyć kopiec testowy
testowanie metod up() i down() - dla każdej:
modyfikacja wartość na wybranej pozycji kopca tak aby własność kopca nie była spełniona,
wywołanie metody dla zmienionej pozycji
wyświetlenie kopca
*/

Heap::Heap(int c)
{
	kopiec = new int[c];
	capacity = c;
	heap_size = 0;
}

Heap::Heap()
{
	capacity = 20;
	kopiec = new int[capacity] {12, 9, 10, 7, 9, 5, 9, 2, 1, 3};
	heap_size = 10;
}

bool Heap::empty()
{
	if (heap_size == 0)
		return true;
	return false;
}

bool Heap::full()
{
	if (heap_size == capacity)
		return true;
	return false;
}

int Heap::left(int i)
{
	if (!empty())
		return 2 * i + 1;
	return NULL;

	/**if (i >= 0)
		return 2 * i + 1;
	return -1;**/
}

int Heap::right(int i)
{
	if (!empty())
		return 2 * i + 2;
	return NULL;

	/**if (i >= 0)
		return 2 * i + 2;
	return -1;**/
}

int Heap::parent(int i)
{
	//jesli i jest korzeniem, to nie ma ojca
	if (((i - 1) / 2) >= 0 && i < heap_size)
		return int((i - 1) / 2);
	return NULL;
}

int Heap::getSize()
{
	return heap_size;
}

void Heap::setHeapSize(int s)
{
	heap_size = s;
}

int Heap::get(int i)
{
	if (i >= 0 && i < heap_size)
		return kopiec[i];
	return NULL;
}

void Heap::set(int i, int x)
{
	kopiec[i] = x;
}

void Heap::up(int i) //i to pozycja, od której zaczynamy wynurzanie
{
	int wartosc_na_pozycji_i;
	int pozycja_ojca_i;
	int wartosc_ojca_i;

	wartosc_na_pozycji_i = get(i);
	pozycja_ojca_i = parent(i);
	wartosc_ojca_i = get(pozycja_ojca_i);

	if (i > 0 && wartosc_na_pozycji_i > wartosc_ojca_i)
	{
		//pierwsza metoda rowniez dziala poprawnie
		//set(i, wartosc_ojca_i);
		//set(pozycja_ojca_i, wartosc_na_pozycji_i);
		swap(kopiec[pozycja_ojca_i], kopiec[i]);
		up(pozycja_ojca_i); //rekurencja
	}
}

void Heap::down(int i) //i to pozycja, od której rozpoczynamy zatapianie
{
	int pozycja_lewego_syna, pozycja_prawego_syna, temp;
	pozycja_lewego_syna = left(i);
	pozycja_prawego_syna = right(i);
	temp = i;

	if (get(pozycja_lewego_syna) > get(i) && pozycja_lewego_syna < heap_size)
		temp = pozycja_lewego_syna;
	if (get(pozycja_prawego_syna) > get(temp) && pozycja_prawego_syna < heap_size)
		temp = pozycja_prawego_syna;

	if (temp != i)
	{
		//pierwsza metoda dziala zle -> lepiej robic z swap
		//int wartosc = get(temp);
		//set(i, get(temp));
		//set(temp, get(i));
		swap(kopiec[i], kopiec[temp]);
		down(temp); //rekurencja
	}
}

ostream& operator<<(ostream& out, Heap& h)
{
	if (h.empty())
		return out;

	for (int i = 0; i < h.heap_size; i++)
	{
		out << h.kopiec[i] << " ";
	}
	return out;
}

int main()
{
	Heap kopiec = Heap();

	cout << kopiec << endl;

	kopiec.set(8, 15);

	kopiec.up(8);

	cout << kopiec << endl;

	kopiec.set(1, 1);

	kopiec.down(1);

	cout << kopiec << endl;
	
	return 0;
}