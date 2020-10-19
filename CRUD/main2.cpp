#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime> 

using namespace std;

struct Mahasiswa {
	int pk;
	string NIM;
	string nama;
	string jurusan;
};

int getOption();
void checkDatabase(fstream &data);
void writeData(fstream &data, int posisi, Mahasiswa &inputMahasiswa);
int getDataSize(fstream &data);
Mahasiswa readData(fstream &data, int posisi);
void addDataMahasiswa(fstream &data);
void displayDataMahasiswa(fstream &data);
void updateRecord(fstream &data);
void deleteRecord(fstream &data);

int main(){

	fstream data;
	
	checkDatabase(data);

	
	int pilihan = getOption();
	char is_continue;

	enum option{CREATE = 1, READ, UPDATE, DELETE, FINISH};

	while(pilihan != FINISH){
		
		switch(pilihan){
			case CREATE:
				cout << "Menambah data mahasiswa" << endl;
				addDataMahasiswa(data);
				break;
			case READ:
				cout << "Tampilkan data mahasiswa" << endl;
				displayDataMahasiswa(data);
				break;
			case UPDATE:
				cout << "Ubah data mahasiswa" << endl;
				displayDataMahasiswa(data);
				updateRecord(data);
				displayDataMahasiswa(data);
				break;
			case DELETE:
				cout << "Hapus data mahasiswa" << endl;
				displayDataMahasiswa(data);
				deleteRecord(data);
				displayDataMahasiswa(data);
				break;
			default:
				cout << "Pilihan tidak ditemukan" << endl;
				break;
		}

		label_continue:

		cout << "Lanjutkan?(y/n) : ";
		cin >> is_continue;
		if ( (is_continue == 'y') | (is_continue == 'Y')){
			pilihan = getOption();
		} else if ((is_continue == 'n') | (is_continue == 'N')){
			break;
		} else {
			goto label_continue;
		}
	}

	cout << "akhir dari program" << endl;
	system("pause 2");
	system("clear");

	cin.get();
	return 0;
}

void writeData(fstream &data, int posisi, Mahasiswa &inputMahasiswa){
	data.seekp((posisi - 1)*sizeof(Mahasiswa), ios::beg);
	data.write(reinterpret_cast<char*>(&inputMahasiswa),sizeof(Mahasiswa));
}

Mahasiswa readData(fstream &data, int posisi){
	Mahasiswa readMahasiswa;
	data.seekg((posisi - 1)*sizeof(Mahasiswa),ios::beg);
	data.read(reinterpret_cast<char*>(&readMahasiswa),sizeof(Mahasiswa));
	return readMahasiswa;
}

void displayDataMahasiswa(fstream &data){
	int size = getDataSize(data);
	Mahasiswa showMahasiswa;
	cout << "no.\tpk.\tNIM.\tNama.\tJurusan." << endl;
	for(int i = 1; i <= size; i++){
		showMahasiswa = readData(data,i);
		cout << i << "\t";
		cout << showMahasiswa.pk << "\t";
		cout << showMahasiswa.NIM << "\t";
		cout << showMahasiswa.nama << "\t";
		cout << showMahasiswa.jurusan << endl;
	}
}

void deleteRecord(fstream &data){
	int nomor, size, offset;
	Mahasiswa blankMahasiswa, tempMahasiswa;
	fstream dataSementara;
	size = getDataSize(data);
	cout << "Hapus nomor: ";
	cin >> nomor;
	writeData(data,nomor,blankMahasiswa);
	dataSementara.open("temp.dat", ios::trunc | ios:: out | ios::in | ios::binary);

	offset = 0;
	for( int i = 1; i <= size; i++){
		tempMahasiswa = readData(data,i);

		if(!tempMahasiswa.nama.empty()){
			writeData(dataSementara,i - offset,tempMahasiswa);
		} else {
			offset++;
			cout << "deleted item" << endl;
		}
	}
	size = getDataSize(dataSementara);
	data.close();
	data.open("data.bin",ios::trunc | ios::out | ios::binary);
	data.close();
	data.open("data.bin",ios::out | ios::in | ios::binary);
	for(int i = 1; i <= size; i++){
		tempMahasiswa = readData(dataSementara,i);
		writeData(data,i,tempMahasiswa);
	}
}
void updateRecord(fstream &data){
	int nomor;
	Mahasiswa updateMahasiswa;
	cout << "pilih no: ";
	cin >> nomor;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	updateMahasiswa = readData(data,nomor);

	cout << "\n\nPilihan data; " << endl;
	cout << "NIM: " << updateMahasiswa.NIM << endl;
	cout << "NIM: " << updateMahasiswa.nama << endl;
	cout << "NIM: " << updateMahasiswa.jurusan << endl;

	cout << "\nMerubah data: " << endl;
	cout << "NIM: ";
	getline(cin,updateMahasiswa.NIM);
	cout << "Nama: ";
	getline(cin,updateMahasiswa.nama);
	cout << "Jurusan: ";
	getline(cin,updateMahasiswa.jurusan);

	writeData(data,nomor,updateMahasiswa);
}

void checkDatabase(fstream &data){
	data.open("data.txt", ios::out | ios::in | ios::binary);

	// check file ada atau tidak
	if (data.is_open()){
		cout << "database ditemukan" << endl;
		system("pause 2"); // windows
	} else {
		cout << "database tidak ditemukan, buat database baru" << endl;
		system("pause 2"); // windows
		data.close();
		data.open("data.bin", ios::trunc | ios::out | ios::in | ios::binary);
	}
}

int getOption(){
	int input;
	system("cls"); // windows

	// menampilkan waktu sekarang
	time_t now = time(0);
	char* dt = ctime(&now);

	cout << "Hari ini:" << dt;

	cout << "\nProgram CRUD data mahasiswa" << endl;
	cout << "=============================" << endl;
	cout << "1. Tambah data mahasiswa" << endl;
	cout << "2. Tampilkan data mahasiswa" << endl;
	cout << "3. Ubah data mahasiswa" << endl;
	cout << "4. Hapus data mahasiswa" << endl;
	cout << "5. Selesai" << endl;
	cout << "=============================" << endl;
	cout << "pilih [1-5]? : ";
	cin >> input;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return input;
}


int getDataSize(fstream &data){
	int start, end;
	data.seekg(0,ios::beg);
	start = data.tellg();
	data.seekg(0,ios::end);
	end = data.tellg();
	return (end-start)/sizeof(Mahasiswa);
}


void addDataMahasiswa(fstream &data){
	
	Mahasiswa inputMahasiswa, lastMahasiswa;

	int size = getDataSize(data);
	
	cout << "ukuran data : " << size << endl;

	if(size == 0){
		inputMahasiswa.pk = 1;
	} else {
		lastMahasiswa = readData(data,size);
		cout << "pk = " << lastMahasiswa.pk << endl;
		inputMahasiswa.pk = lastMahasiswa.pk + 1;
	}

	cout << "Nama: ";
	getline(cin, inputMahasiswa.nama);
	cout << "Jurusan: ";
	getline(cin, inputMahasiswa.jurusan);
	cout << "NIM: ";
	getline(cin, inputMahasiswa.NIM);

	writeData(data,size+1,inputMahasiswa);
}
