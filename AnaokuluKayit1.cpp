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
    cout << "Öðrenci kayýtlarý disk dosyasýna aktarýldý." << endl;
}


    void tumListe() {
        Ogrenci* temp = bas;

        while (temp != NULL) {
            cout << "Ad: " << temp->ad << endl;
            cout << "Soyad: " << temp->soyad << endl;
            cout << "Sýnýf: " << temp->sinif << endl;
            cout << "Doðum Tarihi: " << temp->dogumTarihi << endl;
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
                cout << "Sýnýf: " << temp->sinif << endl;
                cout << "Doðum Tarihi: " << temp->dogumTarihi << endl;
                cout << "Veli Telefonu: " << temp->veliTelefon << endl;
                cout << endl;
                bulundu = true;
            }
            temp = temp->next;
        }

        if (!bulundu) {
            cout << "Belirtilen sýnýfta öðrenci bulunamadý." << endl;
        }
    }
};

int main() {
    AnaokuluKayit kayit;
    string ad, soyad, dogumTarihi, veliTelefon;
    int sinif;
    int devam =0;
    //* Örnek kayýtlar deneme
    kayit.ekle("Ahmet", "Yýlmaz", 1, "01.01.2016", "555-1234567");
    kayit.ekle("Ayþe", "Demir", 2, "05.03.2015", "555-9876543");
    kayit.ekle("Mehmet", "Kaya", 1, "10.07.2016", "555-2468135");
    kayit.ekle("Fatma", "Þahin", 3, "15.09.2014", "555-3698524");

    //Kullanýcýnýn kayýt giriþi 
    while(devam==0){
    cout << "Öðrenci Bilgilerini Girin:" << endl;
    cout << "Ad: ";
    cin >> ad;
    cout << "Soyad: ";
    cin >> soyad;
    cout << "Sýnýf: ";
    cin >> sinif;
    cout << "Doðum Tarihi: ";
    cin >> dogumTarihi;
    cout << "Veli Telefonu: ";
    cin >> veliTelefon;	
    kayit.ekle(ad, soyad, sinif, dogumTarihi, veliTelefon);
    cout << "Baþka öðrenci eklenecekmi evet için 0 hayýr için 1 giriniz";
    cin >> devam;		
	}
    // Öðrenci kayýtlarýnýn listeye aktarýlmasý
    kayit.listeyeAktar();

    // Tüm öðrenci kayýtlarýnýn listelenmesi
    kayit.tumListe();

    // Belirli bir sýnýftaki öðrenci kayýtlarýnýn listelenmesi
    cout << "Listelemek istediðiniz sýnýfý girin: ";
    cin >> sinif;
    kayit.sinifiListele(sinif);

    return 0;
}

