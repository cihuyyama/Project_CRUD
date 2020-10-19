#include <bits/stdc++.h>
using namespace std;

struct Mahasiswa{
    int pk;
    string NIM;
    string nama;
    string jurusan;
};

int getOption();
void chekDatabase(fstream &data);
void writeData(fstream &data, int posisi, Mahasiswa &inputMahasiswa);
int getDataSize(fstream &data);
Mahasiswa readData(fstream &data, int posisi);
void addDatamahasiswa(fstream &data);
void displayDataMahasiswa(fstream &data);

int main(){

    fstream data;
    chekDatabase(data);
   
    int pilihan=getOption();
    char is_continue;

    while (pilihan!=5){
        switch(pilihan){
            case 1:
            cout<<"Menambah data Mahasiswa"<<endl;
            addDatamahasiswa(data);
            break;
            case 2:
            cout<<"Tampilkan data Mahasiswa"<<endl;
            displayDataMahasiswa(data);
            break;
            case 3:
            cout<<"Ubah data Mahasiswa"<<endl;
            break;
            case 4:
            cout<<"Hapus data Mahasiswa"<<endl;
            break;
            default:
            cout<<"Pilihan tidak ditemukan"<<endl;
            break;
        }
        label_continue:
        cout<<"Lanjutkan?(y/n) : ";
        cin>>is_continue;
        if((is_continue=='y')|(is_continue=='Y')){
            pilihan=getOption();
        }
        else if ((is_continue=='n')|(is_continue=='N')){
            break;
        }
        else{
            cout<<"\nPILIHAN TIDAK DITEMUKAN!!!\n"<<endl;
            goto label_continue;
        }
        
    }

    cout<<"Akhir dari program.."<<endl;

    cin.get();
    return 0;
}

int getOption(){
    int input;
    system("cls");
    cout<<"\nProgram CIHUY data Mahasiswa"<<endl;
    cout<<"===================================="<<endl;
    cout<<"1. Tambah data Mahasiswa"<<endl;
    cout<<"2. Tampilkan data Mahasiswa"<<endl;
    cout<<"3. Ubah data Mahasiswa"<<endl;
    cout<<"4. Hapus data Mahasiswa"<<endl;
    cout<<"5. Selesai"<<endl;
    cout<<"===================================="<<endl;
    cout<<"Pilih [1-5]? : ";
    cin>>input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return input;
}

void chekDatabase(fstream &data){
    data.open("data.bin", ios::out|ios::in|ios::binary);
    if(data.is_open()){
        cout<<"data ditemukan"<<endl;
    }
     else{
        cout<<"data tidak ditemukan, Membuat database baru"<<endl;
        data.close();
        data.open("data.bin", ios::trunc|ios::in|ios::out|ios::binary);
    }

}
void writeData(fstream &data, int posisi, Mahasiswa &inputMahasiswa){
    data.seekp((posisi-1)*sizeof(Mahasiswa), ios::beg);
    data.write(reinterpret_cast<char*>(&inputMahasiswa),sizeof(Mahasiswa));
}
int getDataSize(fstream &data){
    int start, end;
    data.seekp(0,ios::beg);
    start=data.tellg();
    data.seekg(0,ios::end);
    end=data.tellg();
    return (end-start)/sizeof(Mahasiswa);
}

Mahasiswa readData(fstream &data, int posisi){
    Mahasiswa readMahasiswa;
    data.seekg((posisi-1)*sizeof(Mahasiswa),ios::beg);
    data.read(reinterpret_cast<char*>(&readMahasiswa),sizeof(Mahasiswa));
    return readMahasiswa;
}

void addDatamahasiswa(fstream &data){
    Mahasiswa inputMahasiswa, lastMahasiswa;

    int size=getDataSize(data);
    cout<<"ukuran data : "<<size<<endl;
    
    if(size==0){
        inputMahasiswa.pk=1;
    }
    else{
        lastMahasiswa=readData(data,size);
        cout<<"pk = :"<<lastMahasiswa.pk<<endl;
        inputMahasiswa.pk=lastMahasiswa.pk+1;
    }

    cout<<"Nama :";
    getline(cin, inputMahasiswa.nama);
    cout<<"NIM :";
    getline(cin, inputMahasiswa.NIM);
    cout<<"Jurusan :";
    getline(cin, inputMahasiswa.jurusan);

    writeData(data,size+1,inputMahasiswa);
}

void displayDataMahasiswa(fstream &data){
    int size = getDataSize(data);
    Mahasiswa showMahasiswa;
    cout<<"no.\tpk.\tNIM\tNama\tJurusan"<<endl;
    for(int i=1;i<=size;i++){
        showMahasiswa=readData(data,i);
        cout<<i<<"\t";
        cout<<showMahasiswa.pk<<"\t";
        cout<<showMahasiswa.NIM<<"\t";
        cout<<showMahasiswa.nama<<"\t";
        cout<<showMahasiswa.jurusan<<"\t";
        cout<<endl;
    }
}