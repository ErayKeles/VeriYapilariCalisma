#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Ogrenci {
    string ad;
    string soyad;
    int sinif;
    string dogumTarihi;
    string veliTelefon;
    Ogrenci* next;
};

class AnaokuluKayit {
private:
    Ogrenci* bas;

public:
    AnaokuluKayit() {
         bas = NULL;
    }

    void ekle(string ad, string soyad, int sinif, string dogumTarihi, string veliTelefon) {
        Ogrenci* yeniOgrenci = new Ogrenci;
        yeniOgrenci->ad = ad;
        yeniOgrenci->soyad = soyad;
        yeniOgrenci->sinif = sinif;
        yeniOgrenci->dogumTarihi = dogumTarihi;
        yeniOgrenci->veliTelefon = veliTelefon;
        yeniOgrenci->next = NULL;

        if (bas == NULL) {
            bas = yeniOgrenci;
        } else {
            Ogrenci* temp = bas;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = yeniOgrenci;
        }
    }

    void listeyeAktar() {
    ofstream dosya("ogrenci_kayitlari.bin", ios::binary | ios::out);
    Ogrenci* temp = bas;

    while (temp != NULL) {
        dosya.write(reinterpret_cast<char*>(&temp), sizeof(Ogrenci));
        temp = temp->next;
    }

    dosya.close();
    cout << "��renci kay�tlar� disk dosyas�na aktar�ld�." << endl;
}


    void tumListe() {
        Ogrenci* temp = bas;

        while (temp != NULL) {
            cout << "Ad: " << temp->ad << endl;
            cout << "Soyad: " << temp->soyad << endl;
            cout << "S�n�f: " << temp->sinif << endl;
            cout << "Do�um Tarihi: " << temp->dogumTarihi << endl;
            cout << "Veli Telefonu: " << temp->veliTelefon << endl;
            cout << endl;
            temp = temp->next;
        }
    }

    void sinifiListele(int sinif) {
        Ogrenci* temp = bas;
        bool bulundu = false;

        while (temp != NULL) {
            if (temp->sinif == sinif) {
                cout << "Ad: " << temp->ad << endl;
                cout << "Soyad: " << temp->soyad << endl;
                cout << "S�n�f: " << temp->sinif << endl;
                cout << "Do�um Tarihi: " << temp->dogumTarihi << endl;
                cout << "Veli Telefonu: " << temp->veliTelefon << endl;
                cout << endl;
                bulundu = true;
            }
            temp = temp->next;
        }

        if (!bulundu) {
            cout << "Belirtilen s�n�fta ��renci bulunamad�." << endl;
        }
    }
};

int main() {
    AnaokuluKayit kayit;
    string ad, soyad, dogumTarihi, veliTelefon;
    int sinif;
    int devam =0;
    //* �rnek kay�tlar deneme
    kayit.ekle("Ahmet", "Y�lmaz", 1, "01.01.2016", "555-1234567");
    kayit.ekle("Ay�e", "Demir", 2, "05.03.2015", "555-9876543");
    kayit.ekle("Mehmet", "Kaya", 1, "10.07.2016", "555-2468135");
    kayit.ekle("Fatma", "�ahin", 3, "15.09.2014", "555-3698524");

    //Kullan�c�n�n kay�t giri�i 
    while(devam==0){
    cout << "��renci Bilgilerini Girin:" << endl;
    cout << "Ad: ";
    cin >> ad;
    cout << "Soyad: ";
    cin >> soyad;
    cout << "S�n�f: ";
    cin >> sinif;
    cout << "Do�um Tarihi: ";
    cin >> dogumTarihi;
    cout << "Veli Telefonu: ";
    cin >> veliTelefon;	
    kayit.ekle(ad, soyad, sinif, dogumTarihi, veliTelefon);
    cout << "Ba�ka ��renci eklenecekmi evet i�in 0 hay�r i�in 1 giriniz";
    cin >> devam;		
	}
    // ��renci kay�tlar�n�n listeye aktar�lmas�
    kayit.listeyeAktar();

    // T�m ��renci kay�tlar�n�n listelenmesi
    kayit.tumListe();

    // Belirli bir s�n�ftaki ��renci kay�tlar�n�n listelenmesi
    cout << "Listelemek istedi�iniz s�n�f� girin: ";
    cin >> sinif;
    kayit.sinifiListele(sinif);

    return 0;
}

