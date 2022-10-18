#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct mahasiswa {
  int no;
  char nama[50];
  char nim[15];
  char tglLahir[20];
  char matkul[30];
};

int getInput() {
  int input;
  
  system("cls");
  cout << "Program CRUD Data Mahasiswa" << endl;
  cout << "===========================" << endl;
  cout << "1. Create Data Mahasiswa" << endl;
  cout << "2. Read Data Mahasiswa" << endl;
  cout << "3. Update Data Mahasiswa" << endl;
  cout << "4. Delete Data Mahasiswa" << endl;
  cout << "5. Selesai" << endl;
  cout << "===========================" << endl;
  cout << "Silahkan masukan pilihan anda [1-5] : ";
  cin >> input;
  cin.ignore();
  return input;
}

void checkDatabase(fstream &data) {

  data.open("data.bin", ios::out | ios::in | ios::binary);

  // check apakah database ada atau tidak
  if (data.is_open()) {
    cout << "database ditemukan" << endl;
  }
  else {
    cout << "database tidak ditemukan, buat database baru" << endl;
    data.close();
    data.open("data.bin", ios::trunc | ios::out | ios::in | ios::binary);
  }
}

void writeData(fstream &data, int position, mahasiswa &inputMahasiswa) {
  data.seekp((position-1)*sizeof(mahasiswa), ios::beg);
  data.write(reinterpret_cast<char*>(&inputMahasiswa),sizeof(mahasiswa));
}

int getDataSize(fstream &data) {
  int start, end;

  data.seekg(0, ios::beg);
  start = data.tellg();
  data.seekg(0, ios::end);
  end = data.tellg();

  return (end-start) / sizeof(mahasiswa);
}

mahasiswa readData(fstream &data, int position) {
  mahasiswa readMahasiswa;
  data.seekg((position - 1)*sizeof(mahasiswa), ios::beg);
  data.read(reinterpret_cast<char*>(&readMahasiswa),sizeof(mahasiswa));
  return readMahasiswa;
}

void addDataMahasiswa(fstream &data) {
  
  mahasiswa inputMahasiswa, lastMahasiswa;

  int size = getDataSize(data);

  cout << "ukuran data : " << size << endl;

  if (size == 0) {
    inputMahasiswa.no = 1;
  } else {
    lastMahasiswa = readData(data, size);
    cout << "no = " << lastMahasiswa.no << endl;
    inputMahasiswa.no = lastMahasiswa.no + 1;
  }

  cout << "Nama\t\t: ";
  cin.get(inputMahasiswa.nama,50);
  cin.ignore();
  cout << "NIM\t\t: ";
  cin.get(inputMahasiswa.nim,15);
  cin.ignore();
  cout << "Tanggal Lahir\t: ";
  cin.get(inputMahasiswa.tglLahir,20);
  cin.ignore();
  cout << "Mata Kuliah\t: ";
  cin.get(inputMahasiswa.matkul,30);
  cin.ignore();

  writeData(data,size+1,inputMahasiswa);
}

void displayDataMahasiswa(fstream &data) {
  int size = getDataSize(data);
  mahasiswa showMahasiswa;

  cout << "No.\tNama\tNIM\tTanggal Lahir\tMata Kuliah" << endl;
  for (int i = 1; i <= size; i++) {
    showMahasiswa = readData(data,i);
    cout << showMahasiswa.no << "\t";
    cout << showMahasiswa.nama << "\t";
    cout << showMahasiswa.nim << "\t";
    cout << showMahasiswa.tglLahir << "\t";
    cout << showMahasiswa.matkul << endl;
  }
}

void updateRecord(fstream &data) {
  int nomor;
  mahasiswa updateMahasiswa;
  cout << "Pilih no: ";
  cin >> nomor;
  cin.ignore();

  updateMahasiswa = readData(data, nomor);
  
  cout << "\n\n pilihan data: " << endl;
  cout << "Nama : " << updateMahasiswa.nama << endl;
  cout << "NIM : " << updateMahasiswa.nim << endl;
  cout << "Tanggal lahir : " << updateMahasiswa.tglLahir << endl;
  cout << "Mata kuliah : " << updateMahasiswa.matkul << endl;

  cout << "\nUbah data: " << endl;
  cin.get(updateMahasiswa.nama,50);
  cin.ignore();
  cout << "NIM\t\t: ";
  cin.get(updateMahasiswa.nim,15);
  cin.ignore();
  cout << "Tanggal Lahir\t: ";
  cin.get(updateMahasiswa.tglLahir,20);
  cin.ignore();
  cout << "Mata Kuliah\t: ";
  cin.get(updateMahasiswa.matkul,30);;
  cin.ignore();

  writeData(data, nomor, updateMahasiswa);

}

void deleteRecord(fstream &data) {
  int nomor,size,offset;
  mahasiswa blankMahasiswa, tempMahasiswa;

  fstream dataTemp;

  size = getDataSize(data);

  cout << "Hapus nomor ke-? : ";
  cin >> nomor;

  writeData(data,nomor,blankMahasiswa);
  
  dataTemp.open("temp.dat", ios::trunc | ios::out | ios::in | ios::binary);

  offset = 0;

  for (int i = 1; i <= size; i++) {
    tempMahasiswa = readData(data, i);

    if (tempMahasiswa.nama[0] != 0) {
      writeData(dataTemp, i - offset, tempMahasiswa);
    } else {
      offset++;
      cout << "deleted item" << endl;
    }
  }

  size = getDataSize(dataTemp);
  data.close();
  data.open("data.bin", ios::trunc | ios::out | ios::binary);
  data.close();
  data.open("data.bin", ios::out | ios::in | ios::binary);

  for (int i = 1; i <= size; i++) {
    tempMahasiswa = readData(dataTemp,i);
    writeData(data,i,tempMahasiswa);
  }
}

int main() {

  fstream data;

  checkDatabase(data);

  int choice = getInput();
  char isContinue;

  enum option{CREATE = 1, READ, UPDATE, DELETE, END}; 

  while (choice != END) {
    
    switch (choice) {
      case CREATE:
        cout << "Create Data Mahasiswa" << endl;
        addDataMahasiswa(data);
        break;
      case READ:
        cout << "Read Data Mahasiswa" << endl;
        displayDataMahasiswa(data);
        break;
      case UPDATE:
        cout << "Update Data Mahasiswa" << endl;
        displayDataMahasiswa(data);
        updateRecord(data);
        displayDataMahasiswa(data);
        break;
      case DELETE:
        cout << "Delete Data Mahasiswa" << endl;
        displayDataMahasiswa(data);
        deleteRecord(data);
        displayDataMahasiswa(data);
        break;
      default:
        cout << "Pilihan anda tidak sesuai" << endl;
        break;
    }

    labelContinue:
    
    cout << "Continue? (y/n) : ";
    cin >> isContinue;
    
    if (isContinue == 'y' | isContinue == 'Y') {
      choice = getInput();
    }
    else if (isContinue == 'n' | isContinue == 'N') {
      break;
    }
    else {
      goto labelContinue;
    }

  }

  cout << "End of Program" << endl;


  return 0;
}
