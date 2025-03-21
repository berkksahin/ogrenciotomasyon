#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Ogrenci {
    string ad;
    string soyad;
    string ogrencino;
    string dogumyili;
    string bolum;
};

struct Ders {
    string ogrencino;
    string derskodu;
    string dersadi;
    int notu;
};

vector<Ogrenci> ogrenciListesi;
vector<Ders> dersListesi;

void DosyadanOgrencileriOku() {
    ifstream dosya("ogrenciler.txt");
    if (!dosya) {
        cout << "Dosya acilamadi." << endl;
        return;
    }

    ogrenciListesi.clear();
    string satir;
    while (getline(dosya, satir)) {
        Ogrenci ogrenci;
        istringstream iss(satir);
        iss >> ogrenci.ad >> ogrenci.soyad >> ogrenci.ogrencino >> ogrenci.dogumyili >> ogrenci.bolum;
        ogrenciListesi.push_back(ogrenci);
    }

    dosya.close();
}

void DosyadanDersleriOku() {
    ifstream dosya("ogrenci_dersler.txt");
    if (!dosya) {
        cout << "Dosya acilamadi." << endl;
        return;
    }

    dersListesi.clear();
    string satir;
    while (getline(dosya, satir)) {
        Ders ders;
        istringstream iss(satir);
        iss >> ders.ogrencino >> ders.derskodu >> ders.dersadi >> ders.notu;
        dersListesi.push_back(ders);
    }

    dosya.close();
}

void OgrenciKaydiEkle() {
    Ogrenci ogrenci;
    cout << "Ad: ";
    cin >> ogrenci.ad;
    cout << "Soyad: ";
    cin >> ogrenci.soyad;
    cout << "Ogrenci No: ";
    cin >> ogrenci.ogrencino;
    cout << "Dogum Yili: ";
    cin >> ogrenci.dogumyili;
    cout << "Bolum: ";
    cin >> ogrenci.bolum;

    ogrenciListesi.push_back(ogrenci);

    ofstream dosya("ogrenciler.txt", ios::app);
    dosya << ogrenci.ad << " " << ogrenci.soyad << " " << ogrenci.ogrencino << " " << ogrenci.dogumyili << " " << ogrenci.bolum << endl;
    dosya.close();

    cout << "Ogrenci kaydi eklendi." << endl;
}

void OgrenciKaydiGuncelle() {
    string ogrencino;
    cout << "Ogrenci No: ";
    cin >> ogrencino;

    bool ogrenciBulundu = false;
    for (Ogrenci& ogrenci : ogrenciListesi) {
        if (ogrenci.ogrencino == ogrencino) {
            ogrenciBulundu = true;
            cout << "Yeni bilgileri girin:" << endl;
            cout << "Ad: ";
            cin >> ogrenci.ad;
            cout << "Soyad: ";
            cin >> ogrenci.soyad;
            cout << "Dogum Yili: ";
            cin >> ogrenci.dogumyili;
            cout << "Bolum: ";
            cin >> ogrenci.bolum;
            cout << "Ogrenci kaydi guncellendi." << endl;
            break;
        }
    }

    if (!ogrenciBulundu) {
        cout << "Ogrenci bulunamadi." << endl;
    }
}

void OgrenciSil() {
    string ogrencino;
    cout << "Ogrenci No: ";
    cin >> ogrencino;

    bool ogrenciBulundu = false;
    for (auto it = ogrenciListesi.begin(); it != ogrenciListesi.end(); ++it) {
        if (it->ogrencino == ogrencino) {
            ogrenciBulundu = true;
            cout << "Ogrenci kaydini silmek istediginizden emin misiniz(E/H)? ";
            char cevap;
            cin >> cevap;
            if (cevap == 'E' || cevap == 'e') {
                ogrenciListesi.erase(it);
                cout << "Ogrenci kaydi silindi." << endl;
            }
            else {
                cout << "Islem iptal edildi." << endl;
            }
            break;
        }
    }

    if (!ogrenciBulundu) {
        cout << "Ogrenci bulunamadi." << endl;
    }
}

void DersSecimiYap() {
    string ogrencino, derskodu, dersadi;
    cout << "Ogrenci No: ";
    cin >> ogrencino;

    bool ogrenciBulundu = false;
    for (const Ogrenci& ogrenci : ogrenciListesi) {
        if (ogrenci.ogrencino == ogrencino) {
            ogrenciBulundu = true;
            break;
        }
    }

    if (!ogrenciBulundu) {
        cout << "Ogrenci bulunamadi." << endl;
        return;
    }

    cout << "Ders Kodu: ";
    cin >> derskodu;
    cout << "Ders Adi: ";
    cin >> dersadi;

    Ders ders;
    ders.ogrencino = ogrencino;
    ders.derskodu = derskodu;
    ders.dersadi = dersadi;
    ders.notu = -1;

    dersListesi.push_back(ders);

    ofstream dosya("ogrenci_dersler.txt", ios::app);
    dosya << ders.ogrencino << " " << ders.derskodu << " " << ders.dersadi << " " << ders.notu << endl;
    dosya.close();

    cout << "Ders secimi yapildi." << endl;
}

void DersSecimiSil() {
    string ogrencino, derskodu;
    cout << "Ogrenci No: ";
    cin >> ogrencino;
    cout << "Ders Kodu: ";
    cin >> derskodu;

    bool kayitBulundu = false;
    for (auto it = dersListesi.begin(); it != dersListesi.end(); ++it) {
        if (it->ogrencino == ogrencino && it->derskodu == derskodu) {
            kayitBulundu = true;
            cout << "Ogrenci ders kaydini silmek istediginizden emin misiniz(E/H)? ";
            char cevap;
            cin >> cevap;
            if (cevap == 'E' || cevap == 'e') {
                dersListesi.erase(it);
                cout << "Ogrenci ders kaydi silindi." << endl;
            }
            else {
                cout << "Islem iptal edildi." << endl;
            }
            break;
        }
    }

    if (!kayitBulundu) {
        cout << "Ogrenci ders kaydi bulunamadi." << endl;
    }
}

void DersNotuGir() {
    string ogrencino, derskodu;
    int notu;
    cout << "Ogrenci No: ";
    cin >> ogrencino;
    cout << "Ders Kodu: ";
    cin >> derskodu;
    cout << "Ders Notu: ";
    cin >> notu;

    bool kayitBulundu = false;
    for (Ders& ders : dersListesi) {
        if (ders.ogrencino == ogrencino && ders.derskodu == derskodu) {
            kayitBulundu = true;
            ders.notu = notu;
            cout << "Ogrenci ders notu kaydedildi." << endl;
            break;
        }
    }

    if (!kayitBulundu) {
        cout << "Ogrenci ders kaydi bulunamadi." << endl;
    }
}

void DersNotuGoruntule() {
    string ogrencino, derskodu;
    cout << "Ogrenci No: ";
    cin >> ogrencino;
    cout << "Ders Kodu: ";
    cin >> derskodu;

    bool kayitBulundu = false;
    for (const Ders& ders : dersListesi) {
        if (ders.ogrencino == ogrencino && ders.derskodu == derskodu) {
            kayitBulundu = true;
            cout << "Ogrencinin ders notu: " << ders.notu << endl;
            break;
        }
    }

    if (!kayitBulundu) {
        cout << "Ogrenci ders kaydi bulunamadi." << endl;
    }
}

void OgrenciTranskripti() {
    ofstream transkript("ogrenci_ders_notlari.txt");
    if (!transkript) {
        cout << "Transkript dosyasi acilamadi." << endl;
        return;
    }

    transkript << "ogrencino derskodu dersadi notu" << endl;

    for (const Ders& ders : dersListesi) {
        transkript << ders.ogrencino << " " << ders.derskodu << " " << ders.dersadi << " " << ders.notu << endl;
    }

    transkript.close();

    cout << "Ogrenci transkripti olusturuldu." << endl;
}

void TumOgrencileriListele() {
    for (const Ogrenci& ogrenci : ogrenciListesi) {
        cout << "Ad: " << ogrenci.ad << endl;
        cout << "Soyad: " << ogrenci.soyad << endl;
        cout << "Ogrenci No: " << ogrenci.ogrencino << endl;
        cout << "Dogum Yili: " << ogrenci.dogumyili << endl;
        cout << "Bolum: " << ogrenci.bolum << endl;
        cout << "------------------------" << endl;
    }
}

int main() {
    DosyadanOgrencileriOku();
    DosyadanDersleriOku();

    while (true) {
        cout << "Ogrenci Isleri Otomasyonu" << endl;
        cout << "(1) Ogrenci Islemleri" << endl;
        cout << "(2) Ders Islemleri" << endl;
        cout << "(3) Raporlar" << endl;
        cout << "(4) Programdan Cikis" << endl;
        cout << "Seciminizi yapin: ";

        int secim;
        cin >> secim;

        switch (secim) {
        case 1:
            while (true) {
                cout << "\nOgrenci Islemleri" << endl;
                cout << "(1) Yeni ogrenci kaydi ekle" << endl;
                cout << "(2) Mevcut ogrenci kaydi guncelle" << endl;
                cout << "(3) Ogrenci sil" << endl;
                cout << "(4) Ust menuye don" << endl;
                cout << "Seciminizi yapin: ";

                int ogrenciSecim;
                cin >> ogrenciSecim;

                switch (ogrenciSecim) {
                case 1:
                    OgrenciKaydiEkle();
                    break;
                case 2:
                    OgrenciKaydiGuncelle();
                    break;
                case 3:
                    OgrenciSil();
                    break;
                case 4:
                    cout << "Ust menuye donuluyor." << endl;
                    break;
                default:
                    cout << "Gecersiz secim. Tekrar deneyin." << endl;
                    break;
                }

                if (ogrenciSecim == 4) {
                    break;
                }
            }
            break;
        case 2:
            while (true) {
                cout << "\nDers Islemleri" << endl;
                cout << "(1) Ogrenci ders secimi yapma" << endl;
                cout << "(2) Ogrenci ders secimi silme" << endl;
                cout << "(3) Ogrenci ders notu girisi" << endl;
                cout << "(4) Ogrenci ders notu goruntuleme" << endl;
                cout << "(5) Ust menuye don" << endl;
                cout << "Seciminizi yapin: ";

                int dersSecim;
                cin >> dersSecim;

                switch (dersSecim) {
                case 1:
                    DersSecimiYap();
                    break;
                case 2:
                    DersSecimiSil();
                    break;
                case 3:
                    DersNotuGir();
                    break;
                case 4:
                    DersNotuGoruntule();
                    break;
                case 5:
                    cout << "Ust menuye donuluyor." << endl;
                    break;
                default:
                    cout << "Gecersiz secim. Tekrar deneyin." << endl;
                    break;
                }

                if (dersSecim == 5) {
                    break;
                }
            }
            break;
        case 3:
            while (true) {
                cout << "\nRaporlar" << endl;
                cout << "(1) Ogrenci transkripti" << endl;
                cout << "(2) Tum ogrencileri listeleme" << endl;
                cout << "(3) Ust menuye don" << endl;
                cout << "Seciminizi yapin: ";

                int raporSecim;
                cin >> raporSecim;

                switch (raporSecim) {
                case 1:
                    OgrenciTranskripti();
                    break;
                case 2:
                    TumOgrencileriListele();
                    break;
                case 3:
                    cout << "Ust menuye donuluyor." << endl;
                    break;
                default:
                    cout << "Gecersiz secim. Tekrar deneyin." << endl;
                    break;
                }

                if (raporSecim == 3) {
                    break;
                }
            }
            break;
        case 4:
            cout << "Program kapatiliyor." << endl;
            return 0;
        default:
            cout << "Gecersiz secim. Tekrar deneyin." << endl;
            break;
        }
    }

    return 0;
}
