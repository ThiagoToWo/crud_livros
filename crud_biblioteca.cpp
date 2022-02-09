#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <cstring>
using std::strcpy;

/*#include <string>
using std::string;*/

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios_base;

/*#include <algorithm>
using std::swap;*/

void titulo();
void adicionar();
void listar();
void editar();
void remover();
void carregar(ifstream&);
void salvar(ofstream&);

struct livro {
	char titulo[100];
	char autor[50];
	char editora[50];
	int edicao;
	int ano;
	int paginas;
};

livro livros[100];

//void sort(livro[], int);

int top  = -1;

int main() {
	ifstream ifs;
	ofstream ofs;
	int opcao;
	
	titulo();
	
	do {
		cout << "Escolha uma opcao:\n"
		     << "\t1 - Adicionar" << "\t5 - Carregar\n"
			 << "\t2 - Listar" << "\t6 - Salvar\n"
			 << "\t3 - Editar" << "\t7 - Sair\n"
			 << "\t4 - Remover\n\n"			 
			 << "Sua escolha: ";
			 
		cin >> opcao;
		cin.get();
		
		switch (opcao) {			
			case 1: adicionar(); break;
			case 2: listar(); break;
			case 3: editar(); break;
			case 4: remover(); break;
			case 5: carregar(ifs); break;
			case 6: salvar(ofs); break;
			default: cout << "Valor invalido";
		}
	} while (opcao != 7);	
}

void adicionar() {
	char opcao;
	
	do {
		char* titulo_;
		char* autor_;
		char* editora_;
		int edicao_;
		int ano_;
		int paginas_;
		
		cout << "Insira o titulo: ";
		cin.getline(livros[++top].titulo, 100);
		cout << "Insira o autor: ";
		cin.getline(livros[top].autor, 50);
		cout << "Insira a editora: ";
		cin.getline(livros[top].editora, 50);
		cout << "Insira a edicao: ";
		cin >> livros[top].edicao;
		cout << "Insira o ano: ";
		cin >> livros[top].ano;
		cout << "Insira o numero de paginas: ";
		cin >> livros[top].paginas;
		
		cout << "Deseja incluir mais algum livro? (S/N): ";		
		cin >> opcao;
		cin.get();
	} while(opcao == 's' || opcao == 'S');
	
	system("cls");
	titulo();
}

void listar() {	
	system("cls");
	titulo();
	
	for (int i = 0; i <= top; i++) {
		cout << (i + 1) << " - " << livros[i].titulo << "; " 
			 << livros[i].autor << "; "
			 << livros[i].editora << "; "
			 << livros[i].edicao << "; "
			 << livros[i].ano << "; "
			 << livros[i].paginas << "\n";
	}
	
	cout << "\n";
}

void editar() {
	char opcao;
	
	do {
		int indice;
		int atributo;
		char* tituloNovo[100];
		char* autorNovo[50];
		char* editoraNovo[50];
		int edicaoNovo;
		int anoNovo;
		int paginasNovo;
		
		listar();
		cout << "Insira o indice do livro a ser editado: ";
		cin >> indice;
		
		cout << "\nInsira o indice do atributo a ser editado\n"
			 << "\t1 - titulo\t4 - edicao\n"
			 << "\t2 - autor\t5 - ano\n"
			 << "\t3 - editora\t6 - paginas\n\n"
			 << "Sua escolha: ";
		cin >> atributo;
		cin.get();
		
		switch (atributo) {
			case 1: 
				cout << "Insira o novo titulo: ";
				cin.getline(livros[indice - 1].titulo, 100);
				break;
			case 2:
				cout << "Insira o novo autor: ";
				cin.getline(livros[indice - 1].autor, 50);
				break;
			case 3: 
				cout << "Insira a nova editora: ";
				cin.getline(livros[indice - 1].editora, 50);
				break;
			case 4:
				cout << "Insira a nova edicao: ";
				cin >> edicaoNovo;
				livros[indice - 1].edicao = edicaoNovo;
				break;
			case 5: 
				cout << "Insira o novo ano: ";
				cin >> anoNovo;
				livros[indice - 1].ano = anoNovo;
				break;
			case 6:
				cout << "Insira o novo numero de paginas: ";
				cin >> paginasNovo;
				livros[indice - 1].paginas = paginasNovo;
				break;
			default: cout << "Valor invalido";
		}
		
		listar();
		cout << "Deseja editar mais algum livro? (S/N): ";		
		cin >> opcao;
	} while (opcao == 's' || opcao == 'S');
	
	system("cls");
	titulo();
}

void remover() {
	char opcao;
	
	do {
		int indice;
		
		listar();
		cout << "Insira o indice do livro a ser removido: ";
		cin >> indice;
		
		for (int i = indice; i <= top; i++) {
			livros[i - 1] = livros[i];
		}
		
		top--;
		
		listar();
		cout << "Deseja incluir mais algum livro? (S/N): ";
		cin >> opcao;
	} while(opcao == 's' || opcao == 'S');
	
	system("cls");
	titulo();
}

void titulo() {
	cout << "***********CRUD_BIBLIOTECA************\n"
		 << "********Administre seus livros********\n\n";
}

void carregar(ifstream& ifs) {
	ifs.open("livros.dat", ios_base::in | ios_base::binary);
	top = -1;
	
	if (!ifs) {
		cerr << "Arquivo nao encontrado\n";
		system("pause");
	} else {
		livro l;
		
		while(ifs.read((char*) &l, sizeof(livro))) {
			livros[++top] = l;
		}
		
		ifs.close();
		
		listar();		
		system("pause");
	}
	
	system("cls");
	titulo();
}

void salvar(ofstream& ofs) {
	ofs.open("livros.dat", ios_base::out | ios_base::binary);
	int n = sizeof(livros) / sizeof(livro);
	//sort(livros, n);
	ofs.write((char*) &livros, sizeof(livro) * (top + 1));	
	ofs.close();
	system("cls");
	titulo();
}

/*void sort(livro l[], int ln) {	
	for (int i = 1; i < ln; i++) {
		for (int j = 0; j < ln - i; j++) {
			string s1(l[j].titulo);
			string s2(l[j + 1].titulo);
			if (s1 > s2) {
				swap(l[j], l[j + 1]);
			}
		}
	}
}*/