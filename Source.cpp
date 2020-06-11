#include "staque.h"

using namespace std;
int main()
{
	//Creating Staque 
	Staque obj;
	//1, 3, 2, 4, 6, 8 , 9 ;
	//Pushing
	obj.push(1);
	obj.push(3);
	obj.push(2);
	obj.push(4);
	obj.push(6);
	obj.push(8);
	obj.push(9);
	//Print
	obj.display();
	//Pop
	obj.pop(2, 1);
	//Print version 2
	for (int i = 0; i < obj.size(); i++) {
		cout << obj[i] << " | " ;
	}
	cout << endl;
	//Testing Other Functions
	obj.pop(2);
	obj.push(13);
	obj.push(12);
	obj.push(49);
	obj.display();
	obj.rdisplay();
	obj.clear();
	obj.display();
}