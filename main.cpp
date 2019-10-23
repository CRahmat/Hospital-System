
//////////////////////////////////////////////////////////
///$$$$   $$$$     $$$$    $$$$$  $$$$$  $$$$$  $$$$$$$///
///$   $  $   $   $    $     $    $      $         $   ///
///$   $  $   $   $    $     $    $      $         $   ///
///$$$$   $$$$    $    $     $    $$$$$  $         $   ///
///$      $ $     $    $  $  $    $      $         $   ///
///$      $   $    $$$$    $$     $$$$$  $$$$$     $   ///
//////////////////////////////////////////////////////////
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <MMSystem.h>
#include <mysql.h>
#include <sstream>
using namespace std;
//PENYIMPANAN
int sv_dk,sv_ky,sv_ob,sv_pn,sv_dp,sv_ao;
int total_biaya;
//MENU PEMERIKSAAN
    int no_pemeriksaan_anak=1,no_pemeriksaan_umum=1,no_pemeriksaan_gigi=1,no_pemeriksaan_syaraf=1,no_pemeriksaan_kandungan=1,no_pemeriksaan_mata=1;
    int jml_pasien,jml_dokter,jml_karyawan;
    int registration_menu=1;
//PENYIMPANAN
int jml_antrian_umum=0;
int jml_antrian_gigi=0;
int jml_antrian_mata=0;
int jml_antrian_anak=0;
int jml_antrian_syaraf=0;
int jml_antrian_kandungan=0;
int pilihan_tampilan_data,data_display=1;
//MENU PENDAFTARAN
int no_antrian_umum,no_antrian_gigi,no_antrian_anak,no_antrian_mata,no_antrian_syaraf,no_antrian_kandungan;
int tampilan_data=1;
//BANTUAN
int kode_obat1,i;
int no_rekam_medis;
int jml_obat,banyak_obat,total;
bool running=true,checking=true;
int jml_hasil_pemeriksaan=0,sound,j,aturan_minum_obat;
//DEKLARASI PROCEDUR
//VOID MENU UTAMA
void status_antrian();
void daftar_dokter();
void apoteker();
void kasir();
void admin();
void edit_data();
void login_dokter();
//VOID PENDAFTARAN
void menu_pendaftaran();
void pendaftaran_pasien_umum();
void pendaftaran_pasien_bpjs();
void pengecekan_NRM_UMUM();
void pengecekan_NRM_BPJS();
//VOID PEMERIKSAAN
void menu_pemeriksaan();
void data_pemeriksaan_pasien();
void pemeriksaan_poli_umum();
void pemeriksaan_poli_gigi();
void pemeriksaan_poli_mata();
void pemeriksaan_poli_anak();
void pemeriksaan_poli_syaraf();
void pemeriksaan_poli_kandungan();
//VOID MENU ADMIN
void pendaftaran_dokter();
void pengecekan_id_dokter();
void pengecekan_poli_dokter();

void pendaftaran_karyawan();
void pengecekan_id_karyawan();
void pengecekan_divisi_karyawan();
void pendaftaran_obat();
void pengecekan_kode_obat();
//VOID OUTPUT DATA
void tampilkan_data();
void tampilkan_data_pasien();
void tampilkan_data_dokter();
void tampilkan_data_karyawan();
void tampilkan_data_obat();
//VOID SEARCHING DAN SHORTING
void tampilkan_data_pasien_searching();
void tampilkan_data_pasien_sorting();
void tampilkan_data_dokter_searching();
void tampilkan_data_dokter_sorting();
void tampilkan_data_karyawan_searching();
void tampilkan_data_karyawan_sorting();
void tampilkan_data_obat_searching();
void tampilkan_data_obat_sorting();
//VOID EDIT DATA
void edit_data_dokter();
void edit_data_karyawan();
void edit_data_obat();
void edit_data_pasien();
void loading_menu_utama();
//VOID TAMBAHAN
void loading();

//DEKLARASI STRUCT
typedef struct
{
    int kode_obat;
    string nama_obat;
    int harga;
} obat;
obat data_obat[100],data_obat_sementara;
typedef struct
{
    string ID;
    string nama;
    string alamat;
    string no_telp;
    int poli;
    string ttl;
    string jenis_kel;
    bool status;
    string password;
} dokter;
dokter data_dokter[100],data_dokter_sementara;
typedef struct
{
    string ID;
    string nama;
    string ttl;
    string jenis_kel;
    string alamat;
    string no_telp;
    int divisi;
} karyawan;
karyawan data_karyawan[100],data_karyawan_sementara;
typedef struct
{
    float berat_badan;
    float tinggi_badan;
    string tensi;
    string hasil;
    string nama_obat;
    int kali_minum;
    int aturan_minum;
} pasien2;
pasien2 data_pemeriksaan_sementara;
typedef struct
{
    string NIK;
    string No_BPJS;
    long int NRM;
    string nama;
    string alamat;
    string jenis_kel;
    string gol_darah;
    int umur;
    string keluhan;
    int poli;
    int biaya;
    bool status_pembayaran;
    bool status_pemeriksaan;
    bool status_pengambilan;
    pasien2 data_pemeriksaan[100];
} pasien;
pasien data_pasien[100],data_pasien_sementara;
//KOORDINAT POSISI
void gotoxy(int x,int y)
{
    COORD CursorPosition = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CursorPosition);
}


//MENU UTAMA --> OK
int main()
{
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
conn = mysql_init(0);conn= mysql_real_connect(conn, "localhost", "root", "", "rumah_sakit", 0, NULL, 0);
if(conn){
        system("COLOR 7A");
    gotoxy(70,22);cout<<"KONEKSI DATABASE BERHASIL!!!\n";
    PlaySound(TEXT("login_berhasil.wav"), NULL, SND_SYNC);
    system("CLS");
}
else{
        system("COLOR 7C");
gotoxy(65,21);cout<<"            KONEKSI GAGAL!!!! \n\n";
gotoxy(65,22);cout<<"TEKAN SPACE UNTUK REFRESH KONEKSI DATABASE\n";
gotoxy(65,23);cout<<"       TEKAN ESCAPE UNTUK KELUAR\n";
PlaySound(TEXT("login_gagal.wav"), NULL, SND_SYNC);
system("PAUSE>NULL");
system("CLS");
if(GetAsyncKeyState(VK_SPACE)){
    main();
}
else{
    exit(0);
}
}
system("COLOR 70");
    //DEKLARASI
    int main_menu;
    if(sound ==0){
    loading_menu_utama();
    gotoxy(65,20);cout<<"           SELAMAT DATANG\n";
    gotoxy(65,21);cout<<"DI RUMAH SAKIT UMUM VETERAN JOGJAKARTA";
    PlaySound(TEXT("Selamat_Datang.wav"), NULL, SND_SYNC);
    }
    sound=1;
    do
    {
        running=true;
        int x=14;
        main_menu=1;
        system("CLS");
        system("COLOR 70");
        gotoxy(54,14);
        cout<<"-->";
        while(running)
        {
            gotoxy(57,9);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,10);
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            gotoxy(57,11);
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            gotoxy(57,12);
            cout<<"|         Jl. RS Veteran No.45, Babasari, Yogyakarta     |\n";
            gotoxy(57,13);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,14);
            cout<<"| PENDAFTARAN                                            |\n";
            gotoxy(57,15);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,16);
            cout<<"| PEMERIKSAAN                                            |\n";
            gotoxy(57,17);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,18);
            cout<<"| KASIR                                                  |\n";
            gotoxy(57,19);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,20);
            cout<<"| APOTEKER                                               |\n";
            gotoxy(57,21);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,22);
            cout<<"| ADMIN                                                  |\n";
            gotoxy(57,23);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,24);
            cout<<" KEY FUNCTION :\n";
            gotoxy(57,25);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            gotoxy(57,26);
            cout<<"| F1   = DAFTAR DOKTER                                   |\n";
            gotoxy(57,27);
            cout<<"| DOWN = SELECT                      UP = SELECT         |\n";
            gotoxy(57,28);
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            if(jml_pasien > 0){
             gotoxy(73,38);cout<<"+=======================+\n";
 gotoxy(73,39);cout<<"|    STATUS ANTRIAN     |\n";
      gotoxy(1,40);
            cout<<setw(167)<<setfill('=')<<"\n";
gotoxy(0,41);
            cout<<setw(27)<<setfill(' ')<<"|"<<setw(28)<<setfill(' ')<<"|"<<setw(28)<<setfill(' ')<<"|"<<setw(28)<<setfill(' ')<<"|"<<setw(27)<<setfill(' ')<<"|\n";
gotoxy(10,41);cout<<"POLI UMUM";
gotoxy(35,41);cout<<"POLI GIGI";
gotoxy(64,41);cout<<"POLI MATA";
gotoxy(92,41);cout<<"POLI ANAK";
gotoxy(118,41);cout<<"POLI SYARAF";
gotoxy(144,41);cout<<"POLI KANDUNGAN";
      gotoxy(1,42);
            cout<<setw(166)<<setfill('=')<<"\n";
            }
            PlaySound(TEXT("pilih_menu.wav"), NULL, SND_SYNC);
            system("PAUSE>NUL");
            system("CLS");
            if(GetAsyncKeyState(VK_UP) && x > 13)
            {
                gotoxy(54,x);
                cout<<"   ";
                x-=2;
                if(x<14)
                {
                    gotoxy(54,22);
                    cout<<"-->";
                    x=22;
                    main_menu=5;
                }
                else
                {
                    gotoxy(54,x);
                    cout<<"-->";
                    main_menu--;
                    continue;
                }
            }

            if(GetAsyncKeyState(VK_DOWN) && x < 23)
            {
                gotoxy(54,x);
                cout<<"   ";
                x+=2;
                if(x>22)
                {
                    gotoxy(54,14);
                    cout<<"-->";
                    x=14;
                    main_menu=1;
                }
                else
                {
                    gotoxy(54,x);
                    cout<<"-->";
                    main_menu++;
                    continue;
                }
            }
            else{
                gotoxy(54,x);
                    cout<<"-->";
            }
            if(GetAsyncKeyState(VK_F1))
            {
                running=false;
                system("CLS");
                daftar_dokter();
            }
            if(GetAsyncKeyState(VK_RETURN))
            {
                switch(main_menu)
                {
                case 1:
                {
                    running=false;
                    system("CLS");
                    menu_pendaftaran();
                    break;
                }
                case 2:
                {
                    running=false;
                    system("CLS");
                    menu_pemeriksaan();
                    break;
                }
                case 3:
                {
                    running=false;
                    system("CLS");
                    kasir();
                    break;
                }
                case 4:
                {
                    running=false;
                    system("CLS");
                    apoteker();
                    break;
                }
                case 5:
                {
                    running=false;
                    system("CLS");
                    admin();
                    break;

                }
                }
            }
        }
    }
    while(main_menu >=1 && main_menu <= 5);
    return 0;
}
void menu_pendaftaran()//OK
{
    system("CLS");
    gotoxy(79,19);
    cout<<"======";
    gotoxy(79,21);
    cout<<"======";
    running=true;
    while(running)
    {
        int registration_menu=1,x=79;
        gotoxy(57,10);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,11);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,12);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,13);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,14);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(84,16);
        cout<<"PASIEN";
        gotoxy(80,20);
        cout<<"UMUM";
        gotoxy(90,20);
        cout<<"BPJS";
        gotoxy(68,23);
        cout<<"TEKAN Esc UNTUK KEMBALI KE MENU UTAMA\n\n";
        gotoxy(0,0);
        PlaySound(TEXT("pilih_menu.wav"), NULL, SND_SYNC);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_RIGHT) && x > 78)
        {
            gotoxy(x,19);
            cout<<"      ";
            gotoxy(x,21);
            cout<<"      ";
            x+=10;
            if(x > 78 && x < 90)
            {
                gotoxy(x,19);
                cout<<"======";
                gotoxy(x,21);
                cout<<"======";
                registration_menu++;
                continue;
            }
            if(x > 89)
            {
                gotoxy(89,19);
                cout<<"======";
                gotoxy(89,21);
                cout<<"======";
                registration_menu=2;
                x=89;
            }
        }
        if(GetAsyncKeyState(VK_LEFT) && x < 90)
        {
            gotoxy(x,19);
            cout<<"      ";
            gotoxy(x,21);
            cout<<"      ";
            x-=10;
            if(x<90 && x > 78)
            {
                gotoxy(x,19);
                cout<<"======";
                gotoxy(x,21);
                cout<<"======";
                registration_menu--;
                continue;
            }
            if(x < 79)
            {
                gotoxy(79,19);
                cout<<"======";
                gotoxy(79,21);
                cout<<"======";
                registration_menu=1;
                x=79;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            main();
        }
        else{
                gotoxy(x,19);
                cout<<"======";
                gotoxy(x,21);
                cout<<"======";
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            switch(registration_menu)
            {
            case 1 :
            {
                running = false;
                system("CLS");
                pendaftaran_pasien_umum();
                break;
            }
            case 2 :
            {
                running = false;
                system("CLS");
                pendaftaran_pasien_bpjs();
                break;
            }

            }
        }
    }
}
void pendaftaran_pasien_umum()
{   //DEKLARASI
    bool cek_NRM=true;
    //SOURCE CODE
    system("CLS");
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                     ---PASIEN UMUM---                  |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"                          WARNING!!!\n\n";
    cout<<"               TEKAN SPACE UNTUK  MELANJUTKAN\n";
    cout<<"                 TEKAN ESCAPE UNTUK KEMBALI\n";
    system("PAUSE>NUL");
    system("CLS");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        menu_pendaftaran();
    }
    else
    {
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                     ---PASIEN UMUM---                  |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : ";//PRIMARY KEY
        cin>>data_pasien_sementara.NRM;
        cout<<endl;
        cout<<"NIK            : ";
        cin>>data_pasien_sementara.NIK;
        cout<<endl;
            if(jml_pasien==0){
            cout<<"NAMA           : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.nama);
            cout<<endl;
            cout<<"UMUR           : ";
            cin>>data_pasien_sementara.umur;
            cout<<endl;
            cout<<"ALAMAT         : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.alamat);
            cout<<endl;
            cout<<"JENIS KELAMIN  : ";
                getline(cin,data_pasien_sementara.jenis_kel);
            cout<<endl;
            cout<<"GOLONGAN DARAH : ";
            cin>>data_pasien_sementara.gol_darah;
            cout<<endl;
                }
            else{
            for(int i=0; i<jml_pasien; i++)
            {
                if(data_pasien[i].NIK == data_pasien_sementara.NIK)
                {
                    cout<<"NAMA           : "<<data_pasien[i].nama;
                    cout<<endl<<endl;
                    cout<<"UMUR           : "<<data_pasien[i].umur;
                    cout<<endl<<endl;
                    cout<<"ALAMAT         : "<<data_pasien[i].alamat;
                    cout<<endl<<endl;
                    cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
                    cout<<endl<<endl;
                    cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
                    cout<<endl<<endl;
                }
                else{
            cout<<"NAMA           : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.nama);
            cout<<endl;
            cout<<"UMUR           : ";
            cin>>data_pasien_sementara.umur;
            cout<<endl;
            cout<<"ALAMAT         : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.alamat);
            cout<<endl;
            cout<<"JENIS KELAMIN  : ";
            getline(cin,data_pasien_sementara.jenis_kel);
            cout<<endl;
            cout<<"GOLONGAN DARAH : ";
            cin>>data_pasien_sementara.gol_darah;
            cout<<endl;
                }
            }
            }
        cout<<"KELUHAN        : ";
        cin.ignore();
        getline(cin, data_pasien_sementara.keluhan);
        cout<<endl;
        cout<<"POLI           : 1. UMUM\n\n";
        cout<<"                 2. GIGI\n\n";
        cout<<"                 3. MATA\n\n";
        cout<<"                 4. ANAK\n\n";
        cout<<"                 5. SYARAF\n\n";
        cout<<"                 6. KANDUNGAN\n\n";
        cout<<"SILAHKAN PILIH POLI UNTUK PASIEN : ";
        cin>>data_pasien_sementara.poli;
        cout<<endl;
        loading();
        pengecekan_NRM_UMUM();
    }
}
void pengecekan_NRM_UMUM()
{
    //DEKLARASI VARIABLE
    bool cek_NRM=true;
    //SOURCE CODE
    if(jml_pasien>0)
    {
        do{
        for(int i=0; i<jml_pasien; i++)
        {
            if(data_pasien_sementara.NRM==data_pasien[i].NRM)
            {
                cek_NRM=false;
                cout<<"NOMOR REKAM MEDIS YANG ANDA MASSUKAN SUDAH TERDAFTAR!!!\n";
                cout<<"    SILAHKAN MASSUKAN NO REKAM MEDIS YANG BERBEDA\n\n";
                system("PAUSE");
                system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PASIEN UMUM---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"NIK            : "<<data_pasien_sementara.NIK<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien_sementara.nama<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien_sementara.umur<<endl<<endl;
            cout<<"ALAMAT         : "<<data_pasien_sementara.alamat<<endl<<endl;
            cout<<"JENIS KELAMIN  : "<<data_pasien_sementara.jenis_kel<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien_sementara.gol_darah<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien_sementara.keluhan<<endl<<endl;
            if(data_pasien_sementara.poli==1)
                    {
                        cout<<"|POLI           : UMUM"<<endl;
                    }
                    else if(data_pasien_sementara.poli==2)
                    {
                        cout<<"|POLI           : GIGI"<<endl;
                    }
                    else if(data_pasien_sementara.poli==3)
                    {
                        cout<<"|POLI           : MATA"<<endl;
                    }
                    else if(data_pasien_sementara.poli==4)
                    {
                        cout<<"|POLI           : ANAK"<<endl;
                    }
                    else if(data_pasien_sementara.poli==5)
                    {
                        cout<<"|POLI           : SYARAF"<<endl;
                    }
                    else if(data_pasien_sementara.poli==6)
                    {
                        cout<<"|POLI           : KANDUNGAN"<<endl;
                    }
                    cout<<endl;
            cout<<"No.REK MEDIS   : ";
            cin>>data_pasien_sementara.NRM;
            cout<<endl;
            loading();
            system("CLS");
            }
            else if(data_pasien_sementara.NRM!=data_pasien[i].NRM && data_pasien[i].status_pemeriksaan==false)
            {
                cek_NRM=true;
                data_pasien[sv_pn].NIK=data_pasien_sementara.NIK;
                data_pasien[sv_pn].NRM=data_pasien_sementara.NRM;
                data_pasien[sv_pn].nama=data_pasien_sementara.nama;
                data_pasien[sv_pn].umur=data_pasien_sementara.umur;
                data_pasien[sv_pn].alamat=data_pasien_sementara.alamat;
                data_pasien[sv_pn].jenis_kel=data_pasien_sementara.jenis_kel;
                data_pasien[sv_pn].gol_darah=data_pasien_sementara.gol_darah;
                data_pasien[sv_pn].keluhan=data_pasien_sementara.keluhan;
                data_pasien[sv_pn].poli=data_pasien_sementara.poli;
                data_pasien[sv_pn].status_pemeriksaan=false;
                data_pasien[sv_pn].status_pembayaran=false;
                data_pasien[sv_pn].status_pengambilan=false;
                cout<<endl<<endl;
                if(data_pasien[sv_pn].poli==1)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI UMUM"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_umum;
                }
                else if(data_pasien[sv_pn].poli==2)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI GIGI"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_gigi;
                }
                else if(data_pasien[sv_pn].poli==3)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI MATA"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_mata;
                }
                else if(data_pasien[sv_pn].poli==4)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI ANAK"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_anak;
                }
                else if(data_pasien[sv_pn].poli==5)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI SYARAF"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_syaraf;
                }
                else if(data_pasien[sv_pn].poli==6)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI KANDUNGAN"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_kandungan;
                }
                cout<<endl<<endl;
                cout<<"Tekan Tombol SPACE Untuk Print Data Pasien"<<endl;
                system("PAUSE>NUL");
                if(GetAsyncKeyState(VK_SPACE))
                {
                    system("CLS");
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|                     ---PASIEN UMUM---                  |\n";
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|NOMOR ANTRIAN  : ";
                    if(data_pasien[sv_pn].poli==1)
                    {
                        cout<<no_pemeriksaan_umum;
                        no_pemeriksaan_umum++;
                    }
                    else if(data_pasien[sv_pn].poli==2)
                    {
                        cout<<no_pemeriksaan_gigi;
                        no_pemeriksaan_gigi++;
                    }
                    else if(data_pasien[sv_pn].poli=3)
                    {
                        cout<<no_pemeriksaan_mata;
                        no_pemeriksaan_mata++;
                    }
                    else if(data_pasien[sv_pn].poli==4)
                    {
                        cout<<no_pemeriksaan_anak;
                        no_pemeriksaan_anak++;
                    }
                    else if(data_pasien[sv_pn].poli==5)
                    {
                        cout<<no_pemeriksaan_syaraf;
                        no_pemeriksaan_syaraf++;
                    }
                    else if(data_pasien[sv_pn].poli==6)
                    {
                        cout<<no_pemeriksaan_kandungan;
                        no_pemeriksaan_kandungan++;
                    }
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|NIK            : "<<data_pasien[sv_pn].NIK;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|No.REK MEDIS   : "<<data_pasien[sv_pn].NRM;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|NAMA           : "<<data_pasien[sv_pn].nama;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|UMUR           : "<<data_pasien[sv_pn].umur;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|ALAMAT         : "<<data_pasien[sv_pn].alamat;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|JENIS KELAMIN  : "<<data_pasien[sv_pn].jenis_kel;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|GOLONGAN DARAH : "<<data_pasien[sv_pn].gol_darah;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|KELUHAN        : "<<data_pasien[sv_pn].keluhan;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    if(data_pasien[sv_pn].poli==1)
                    {
                        cout<<"|POLI           : UMUM"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==2)
                    {
                        cout<<"|POLI           : GIGI"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==3)
                    {
                        cout<<"|POLI           : MATA"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==4)
                    {
                        cout<<"|POLI           : ANAK"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==5)
                    {
                        cout<<"|POLI           : SYARAF"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==6)
                    {
                        cout<<"|POLI           : KANDUNGAN"<<endl;
                    }
                    cout<<"+"<<setw(59)<<setfill('=')<<"+\n\n";
                }
                cout<<"BIAYA REGISTRASI PASIEN  Rp.2000,00\n\n";
                system("PAUSE");
                system("CLS");
            }
        }
        }while(cek_NRM==false);
    }
        else if(jml_pasien==0)
    {
        cek_NRM=true;
        data_pasien[sv_pn].NIK=data_pasien_sementara.NIK;
        data_pasien[sv_pn].NRM=data_pasien_sementara.NRM;
        data_pasien[sv_pn].nama=data_pasien_sementara.nama;
        data_pasien[sv_pn].umur=data_pasien_sementara.umur;
        data_pasien[sv_pn].alamat=data_pasien_sementara.alamat;
        data_pasien[sv_pn].jenis_kel=data_pasien_sementara.jenis_kel;
        data_pasien[sv_pn].gol_darah=data_pasien_sementara.gol_darah;
        data_pasien[sv_pn].keluhan=data_pasien_sementara.keluhan;
        data_pasien[sv_pn].poli=data_pasien_sementara.poli;
        data_pasien[sv_pn].status_pemeriksaan=false;
        data_pasien[sv_pn].status_pembayaran=false;
        data_pasien[sv_pn].status_pengambilan=false;
        cout<<endl<<endl;
        if(data_pasien[sv_pn].poli==1)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI UMUM"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_umum;
        }
        else if(data_pasien[sv_pn].poli==2)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI GIGI"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_gigi;
        }
        else if(data_pasien[sv_pn].poli==3)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI MATA"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_mata;
        }
        else if(data_pasien[sv_pn].poli==4)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI ANAK"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_anak;
        }
        else if(data_pasien[sv_pn].poli==5)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI SYARAF"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_syaraf;
        }
        else if(data_pasien[sv_pn].poli==6)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI KANDUNGAN"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_kandungan;
        }
        cout<<endl<<endl;
        cout<<"Tekan Tombol SPACE Untuk Print Data Pasien"<<endl;
        system("PAUSE>NUL");
        if(GetAsyncKeyState(VK_SPACE))
        {
            system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PASIEN UMUM---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NOMOR ANTRIAN  : ";
            if(data_pasien[sv_pn].poli==1)
            {
                cout<<no_pemeriksaan_umum;
                no_pemeriksaan_umum++;
            }
            else if(data_pasien[sv_pn].poli==2)
            {
                cout<<no_pemeriksaan_gigi;
                no_pemeriksaan_gigi++;
            }
            else if(data_pasien[sv_pn].poli=3)
            {
                cout<<no_pemeriksaan_mata;
                no_pemeriksaan_mata++;
            }
            else if(data_pasien[sv_pn].poli==4)
            {
                cout<<no_pemeriksaan_anak;
                no_pemeriksaan_anak++;
            }
            else if(data_pasien[sv_pn].poli==5)
            {
                cout<<no_pemeriksaan_syaraf;
                no_pemeriksaan_syaraf++;
            }
            else if(data_pasien[sv_pn].poli==6)
            {
                cout<<no_pemeriksaan_kandungan;
                no_pemeriksaan_kandungan++;
            }
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NIK            : "<<data_pasien[sv_pn].NIK;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|No.REK MEDIS   : "<<data_pasien[sv_pn].NRM;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NAMA           : "<<data_pasien[sv_pn].nama;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|UMUR           : "<<data_pasien[sv_pn].umur;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|ALAMAT         : "<<data_pasien[sv_pn].alamat;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|JENIS KELAMIN  : "<<data_pasien[sv_pn].jenis_kel;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|GOLONGAN DARAH : "<<data_pasien[sv_pn].gol_darah;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|KELUHAN        : "<<data_pasien[sv_pn].keluhan;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            if(data_pasien[sv_pn].poli==1)
            {
                cout<<"|POLI           : UMUM"<<endl;
            }
            else if(data_pasien[sv_pn].poli==2)
            {
                cout<<"|POLI           : GIGI"<<endl;
            }
            else if(data_pasien[sv_pn].poli==3)
            {
                cout<<"|POLI           : MATA"<<endl;
            }
            else if(data_pasien[sv_pn].poli==4)
            {
                cout<<"|POLI           : ANAK"<<endl;
            }
            else if(data_pasien[sv_pn].poli==5)
            {
                cout<<"|POLI           : SYARAF"<<endl;
            }
            else if(data_pasien[sv_pn].poli==6)
            {
                cout<<"|POLI           : KANDUNGAN"<<endl;
            }
            cout<<"+"<<setw(59)<<setfill('=')<<"+\n\n";
        }
        cout<<"BIAYA REGISTRASI PASIEN  Rp.2000,00\n\n";
        system("PAUSE");
        system("CLS");
    }
        sv_pn++;
        jml_pasien++;
}
void pendaftaran_pasien_bpjs()
{
    //DEKLARASI VARIABLE
    bool cek_NRM=true;
    //SOURCE CODE
    system("CLS");
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                     ---PASIEN BPJS---                  |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"                          WARNING!!!\n\n";
    cout<<"               TEKAN SPACE UNTUK  MELANJUTKAN\n";
    cout<<"                 TEKAN ESCAPE UNTUK KEMBALI\n";
    system("PAUSE>NUL");
    system("CLS");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        menu_pendaftaran();
    }
    else if(GetAsyncKeyState(VK_SPACE))
    {
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                     ---PASIEN BPJS---                  |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : ";//PRIMARY KEY
        cin>>data_pasien_sementara.NRM;
        cout<<endl;
        cout<<"NO.BPJS        : ";
        cin>>data_pasien_sementara.No_BPJS;
        cout<<endl;
            if(jml_pasien==0){
            cout<<"NAMA           : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.nama);
            cout<<endl;
            cout<<"UMUR           : ";
            cin>>data_pasien_sementara.umur;
            cout<<endl;
            cout<<"ALAMAT         : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.alamat);
            cout<<endl;
            cout<<"JENIS KELAMIN  : ";
            getline(cin,data_pasien_sementara.jenis_kel);
            cout<<endl;
            cout<<"GOLONGAN DARAH : ";
            cin>>data_pasien_sementara.gol_darah;
            cout<<endl;
                }
            else{
            for(int i=0; i<jml_pasien; i++)
            {
                if(data_pasien_sementara.No_BPJS == data_pasien[i].No_BPJS)
                {
                    cout<<"NAMA           : "<<data_pasien[i].nama;
                    cout<<endl<<endl;
                    cout<<"UMUR           : "<<data_pasien[i].umur;
                    cout<<endl<<endl;
                    cout<<"ALAMAT         : "<<data_pasien[i].alamat;
                    cout<<endl<<endl;
                    cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
                    cout<<endl<<endl;
                    cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
                    cout<<endl<<endl;
                }
                else{
                                     cout<<"NAMA           : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.nama);
            cout<<endl;
            cout<<"UMUR           : ";
            cin>>data_pasien_sementara.umur;
            cout<<endl;
            cout<<"ALAMAT         : ";
            cin.ignore();
            getline(cin, data_pasien_sementara.alamat);
            cout<<endl;
            cout<<"JENIS KELAMIN  : ";
            getline(cin,data_pasien_sementara.jenis_kel);
            cout<<endl;
            cout<<"GOLONGAN DARAH : ";
            cin>>data_pasien_sementara.gol_darah;
            cout<<endl;
                }
            }
            }
        cout<<"KELUHAN        : ";
        cin.ignore();
        getline(cin, data_pasien_sementara.keluhan);
        cout<<endl;
        cout<<"POLI           : 1. UMUM\n\n";
        cout<<"                 2. GIGI\n\n";
        cout<<"                 3. MATA\n\n";
        cout<<"                 4. ANAK\n\n";
        cout<<"                 5. SYARAF\n\n";
        cout<<"                 6. KANDUNGAN\n\n";
        cout<<"SILAHKAN PILIH POLI UNTUK PASIEN : ";
        cin>>data_pasien_sementara.poli;
        cout<<endl;
        loading();
        pengecekan_NRM_BPJS();
    }
    else{
        pendaftaran_pasien_bpjs();
    }
}
void pengecekan_NRM_BPJS()
{
    //DEKLARASI
    bool cek_NRM=true;
    //SOURCE CODE
    if(jml_pasien>0)
    {
        do{
        for(int i=0; i<jml_pasien; i++)
        {
                        if(data_pasien[i].NRM==data_pasien_sementara.NRM)
            {
                cek_NRM=false;
                cout<<"NOMOR REKAM MEDIS YANG ANDA MASSUKAN SUDAH TERDAFTAR!!!\n";
                cout<<"    SILAHKAN MASSUKAN NO REKAM MEDIS YANG BERBEDA\n\n";
                system("PAUSE");
                system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PASIEN BPJS---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"NO BPJS        : "<<data_pasien_sementara.No_BPJS<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien_sementara.nama<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien_sementara.umur<<endl<<endl;
            cout<<"ALAMAT         : "<<data_pasien_sementara.alamat<<endl<<endl;
            cout<<"JENIS KELAMIN  : "<<data_pasien_sementara.jenis_kel<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien_sementara.gol_darah<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien_sementara.keluhan<<endl<<endl;
            if(data_pasien[sv_pn].poli==1)
                    {
            cout<<"POLI           : UMUM"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==2)
                    {
                        cout<<"POLI           : GIGI"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==3)
                    {
                        cout<<"POLI           : MATA"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==4)
                    {
                        cout<<"POLI           : ANAK"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==5)
                    {
                        cout<<"POLI           : SYARAF"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==6)
                    {
                        cout<<"POLI           : KANDUNGAN"<<endl;
                    }
                    cout<<endl;
            cout<<"No.REK MEDIS   : ";
            cin>>data_pasien_sementara.NRM;
            cout<<endl;
            loading();
            system("PAUSE");
            system("CLS");
            }
            else if(data_pasien[i].NRM!=data_pasien_sementara.NRM)
            {
                cek_NRM=true;
                data_pasien[sv_pn].No_BPJS=data_pasien_sementara.No_BPJS;
                data_pasien[sv_pn].NRM=data_pasien_sementara.NRM;
                data_pasien[sv_pn].nama=data_pasien_sementara.nama;
                data_pasien[sv_pn].umur=data_pasien_sementara.umur;
                data_pasien[sv_pn].alamat=data_pasien_sementara.alamat;
                data_pasien[sv_pn].jenis_kel=data_pasien_sementara.jenis_kel;
                data_pasien[sv_pn].gol_darah=data_pasien_sementara.gol_darah;
                data_pasien[sv_pn].keluhan=data_pasien_sementara.keluhan;
                data_pasien[sv_pn].poli=data_pasien_sementara.poli;
                data_pasien[sv_pn].status_pemeriksaan=false;
                data_pasien[sv_pn].status_pembayaran=false;
                data_pasien[sv_pn].status_pengambilan=false;
                cout<<endl<<endl;
                if(data_pasien[sv_pn].poli==1)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI UMUM"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_umum;
                }
                else if(data_pasien[sv_pn].poli==2)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI GIGI"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_gigi;
                }
                else if(data_pasien[sv_pn].poli==3)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI MATA"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_mata;
                }
                else if(data_pasien[sv_pn].poli==4)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI ANAK"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_anak;
                }
                else if(data_pasien[sv_pn].poli==5)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI SYARAF"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_syaraf;
                }
                else if(data_pasien[sv_pn].poli==6)
                {
                    cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI KANDUNGAN"<<endl<<endl;
                    cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_kandungan;
                }
                cout<<endl<<endl;
                cout<<"Tekan Tombol SPACE Untuk Print Data Pasien"<<endl;
                system("PAUSE>NUL");
                if(GetAsyncKeyState(VK_SPACE))
                {
                    system("CLS");
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|                     ---PASIEN BPJS---                  |\n";
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|NOMOR ANTRIAN  : ";
                    if(data_pasien[sv_pn].poli==1)
                    {
                        cout<<no_pemeriksaan_umum;
                        no_pemeriksaan_umum++;
                    }
                    else if(data_pasien[sv_pn].poli==2)
                    {
                        cout<<no_pemeriksaan_gigi;
                        no_pemeriksaan_gigi++;
                    }
                    else if(data_pasien[sv_pn].poli=3)
                    {
                        cout<<no_pemeriksaan_mata;
                        no_pemeriksaan_mata++;
                    }
                    else if(data_pasien[sv_pn].poli==4)
                    {
                        cout<<no_pemeriksaan_anak;
                        no_pemeriksaan_anak++;
                    }
                    else if(data_pasien[sv_pn].poli==5)
                    {
                        cout<<no_pemeriksaan_syaraf;
                        no_pemeriksaan_syaraf++;
                    }
                    else if(data_pasien[sv_pn].poli==6)
                    {
                        cout<<no_pemeriksaan_kandungan;
                        no_pemeriksaan_kandungan++;
                    }
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|NIK            : "<<data_pasien[sv_pn].No_BPJS;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|No.REK MEDIS   : "<<data_pasien[sv_pn].NRM;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|NAMA           : "<<data_pasien[sv_pn].nama;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|UMUR           : "<<data_pasien[sv_pn].umur;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|ALAMAT         : "<<data_pasien[sv_pn].alamat;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|JENIS KELAMIN  : "<<data_pasien[sv_pn].jenis_kel;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|GOLONGAN DARAH : "<<data_pasien[sv_pn].gol_darah;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    cout<<"|KELUHAN        : "<<data_pasien[sv_pn].keluhan;
                    cout<<endl;
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                    if(data_pasien[sv_pn].poli==1)
                    {
                        cout<<"|POLI           : UMUM"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==2)
                    {
                        cout<<"|POLI           : GIGI"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==3)
                    {
                        cout<<"|POLI           : MATA"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==4)
                    {
                        cout<<"|POLI           : ANAK"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==5)
                    {
                        cout<<"|POLI           : SYARAF"<<endl;
                    }
                    else if(data_pasien[sv_pn].poli==6)
                    {
                        cout<<"|POLI           : KANDUNGAN"<<endl;
                    }
                    cout<<"+"<<setw(59)<<setfill('=')<<"+\n\n";
                                    system("PAUSE");
                system("CLS");
                }
            }
        }
        }while(cek_NRM==false);
    }
    if(jml_pasien==0)
    {
        cek_NRM=true;
        data_pasien[sv_pn].No_BPJS=data_pasien_sementara.No_BPJS;
        data_pasien[sv_pn].NRM=data_pasien_sementara.NRM;
        data_pasien[sv_pn].nama=data_pasien_sementara.nama;
        data_pasien[sv_pn].umur=data_pasien_sementara.umur;
        data_pasien[sv_pn].alamat=data_pasien_sementara.alamat;
        data_pasien[sv_pn].jenis_kel=data_pasien_sementara.jenis_kel;
        data_pasien[sv_pn].gol_darah=data_pasien_sementara.gol_darah;
        data_pasien[sv_pn].keluhan=data_pasien_sementara.keluhan;
        data_pasien[sv_pn].poli=data_pasien_sementara.poli;
        data_pasien[sv_pn].status_pemeriksaan=false;
                data_pasien[sv_pn].status_pembayaran=false;
                data_pasien[sv_pn].status_pengambilan=false;
        cout<<endl<<endl;
        if(data_pasien[sv_pn].poli==1)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI UMUM"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_umum;
        }
        else if(data_pasien[sv_pn].poli==2)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI GIGI"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_gigi;
        }
        else if(data_pasien[sv_pn].poli==3)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI MATA"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_mata;
        }
        else if(data_pasien[sv_pn].poli==4)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI ANAK"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_anak;
        }
        else if(data_pasien[sv_pn].poli==5)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI SYARAF"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_syaraf;
        }
        else if(data_pasien[sv_pn].poli==6)
        {
            cout<<"PASIEN DENGAN NAMA "<<data_pasien[sv_pn].nama<<" TELAH TERDAFTAR DI POLI KANDUNGAN"<<endl<<endl;
            cout<<"NOMOR ANTRIAN  : "<<no_pemeriksaan_kandungan;
        }
        cout<<endl<<endl;
        cout<<"Tekan Tombol SPACE Untuk Print Data Pasien"<<endl;
        system("PAUSE>NUL");
        if(GetAsyncKeyState(VK_SPACE))
        {
            system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PASIEN BPJS---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NOMOR ANTRIAN  : ";
            if(data_pasien[sv_pn].poli==1)
            {
                cout<<no_pemeriksaan_umum;
                no_pemeriksaan_umum++;
            }
            else if(data_pasien[sv_pn].poli==2)
            {
                cout<<no_pemeriksaan_gigi;
                no_pemeriksaan_gigi++;
            }
            else if(data_pasien[sv_pn].poli=3)
            {
                cout<<no_pemeriksaan_mata;
                no_pemeriksaan_mata++;
            }
            else if(data_pasien[sv_pn].poli==4)
            {
                cout<<no_pemeriksaan_anak;
                no_pemeriksaan_anak++;
            }
            else if(data_pasien[sv_pn].poli==5)
            {
                cout<<no_pemeriksaan_syaraf;
                no_pemeriksaan_syaraf++;
            }
            else if(data_pasien[sv_pn].poli==6)
            {
                cout<<no_pemeriksaan_kandungan;
                no_pemeriksaan_kandungan++;
            }
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|No.BPJS         : "<<data_pasien[sv_pn].No_BPJS;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|No.REK MEDIS   : "<<data_pasien[sv_pn].NRM;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NAMA           : "<<data_pasien[sv_pn].nama;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|UMUR           : "<<data_pasien[sv_pn].umur;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|ALAMAT         : "<<data_pasien[sv_pn].alamat;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|JENIS KELAMIN  : "<<data_pasien[sv_pn].jenis_kel;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|GOLONGAN DARAH : "<<data_pasien[sv_pn].gol_darah;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|KELUHAN        : "<<data_pasien[sv_pn].keluhan;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            if(data_pasien[sv_pn].poli==1)
            {
            cout<<"|POLI           : UMUM"<<endl;
            }
            else if(data_pasien[sv_pn].poli==2)
            {
                cout<<"|POLI           : GIGI"<<endl;
            }
            else if(data_pasien[sv_pn].poli==3)
            {
                cout<<"|POLI           : MATA"<<endl;
            }
            else if(data_pasien[sv_pn].poli==4)
            {
                cout<<"|POLI           : ANAK"<<endl;
            }
            else if(data_pasien[sv_pn].poli==5)
            {
                cout<<"|POLI           : SYARAF"<<endl;
            }
            else if(data_pasien[sv_pn].poli==6)
            {
                cout<<"|POLI           : KANDUNGAN"<<endl;
            }
            cout<<"+"<<setw(59)<<setfill('=')<<"+\n\n";
        }
        cout<<"BIAYA REGISTRASI PASIEN GRATIS\n\n";
        system("PAUSE");
        system("CLS");
    }
        sv_pn++;
        jml_pasien++;
}
void menu_pemeriksaan()
{
    //DEKLARASI
    if(jml_obat==0 || jml_pasien==0 || data_dokter[0].status==false){
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                     ---PEMERIKSAAN---                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,18);cout<<"MENU PEMERIKSAAN BELUM DAPAT DI AKSES\n\n";
        if(jml_pasien==0){
        gotoxy(62,21);cout<<"SISTEM MENDETEKSI BELUM TERDAPAT PASIEN TERDAFTAR\n\n";
        }
        if(jml_obat==0){
        gotoxy(63,22);cout<<"SISTEM MENDETEKSI BELUM TERDAPAT OBAT TERDAFTAR\n\n";
        }
        if(data_dokter[0].status==false){
        gotoxy(64,23);cout<<"SISTEM MENDETEKSI BELUM TERDAPAT DOKTER LOGIN\n\n";
        }
        gotoxy(72,25);system("PAUSE");
        system("CLS");

    }
    else{
        int poli_pemeriksaan=1,x=18;
    //SOURCE CODE
    gotoxy(54,18);
    cout<<"-->";
    bool running=true;
    while(running)
    {
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                     ---PEMERIKSAAN---                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,18);
        cout<<"|POLI UMUM                                               |\n";
        gotoxy(57,19);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,20);
        cout<<"|POLI GIGI                                               |\n";
        gotoxy(57,21);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,22);
        cout<<"|POLI MATA                                               |\n";
        gotoxy(57,23);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,24);
        cout<<"|POLI ANAK                                               |\n";
        gotoxy(57,25);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,26);
        cout<<"|POLI SYARAF                                             |\n";
        gotoxy(57,27);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,28);
        cout<<"|POLI KANDUNGAN                                          |\n";
        gotoxy(57,29);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,30);
        cout<<"TEKAN esc UNTUK KEMBALI KE MENU UTAMA\n";
        PlaySound(TEXT("pilih_menu.wav"), NULL, SND_SYNC);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_UP) && x > 17)
        {
            gotoxy(54,x);
            cout<<"   ";
            x-=2;
            if(x<=18)
            {
                gotoxy(54,18);
                cout<<"-->";
                x=18;
                poli_pemeriksaan=1;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                poli_pemeriksaan--;
                continue;
            }
        }

        if(GetAsyncKeyState(VK_DOWN) && x < 29)
        {
            gotoxy(54,x);
            cout<<"   ";
            x+=2;
            if(x>28)
            {
                gotoxy(54,18);
                cout<<"-->";
                x=18;
                poli_pemeriksaan=1;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                poli_pemeriksaan++;
                continue;
            }
        }
        if(x==18){
            poli_pemeriksaan=1;
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            running=false;
            system("CLS");
            main();
        }
        else{
            gotoxy(54,x);
                cout<<"-->";
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            switch(poli_pemeriksaan)
            {
            case 1:
            {
                running=false;
                system("CLS");
                pemeriksaan_poli_umum();
                break;
            }
            case 2:
            {
                running=false;
                system("CLS");
                pemeriksaan_poli_gigi();
                break;
            }
            case 3:
            {
                running=false;
                system("CLS");
                pemeriksaan_poli_mata();
                break;
            }
            case 4:
            {
                running=false;
                system("CLS");
                pemeriksaan_poli_anak();
                break;
            }
            case 5:
            {
                running=false;
                system("CLS");
                pemeriksaan_poli_syaraf();
                break;

            }
            case 6:
            {
                running=false;
                system("CLS");
                pemeriksaan_poli_kandungan();
                break;
            }
            }
        }
    }
    }

}
void loading()
{
   cout<<"Loading";
   for(int i=0;i<20;i++){
    if(i<15){
        cout<<".";
        Sleep(100);
    }
    if(i<18 && i > 15){
        cout<<".";
        Sleep(200);
    }
    if(i>18 && i<=20){
        cout<<".";
        Sleep(500);
    }
   }
   cout<<endl<<endl;
}
void pemeriksaan_poli_umum()
{
    gotoxy(77,24);
    cout<<" ---POLI UMUM---";
    gotoxy(77,25);
    cout<<"NOMOR REKAM MEDIS";
    gotoxy(77,26);
    cout<<"       ";
    cin>>no_rekam_medis;
    int total=0;
    for(int i=0;i<jml_pasien;i++){
            if(data_pasien[i].NRM==no_rekam_medis){
                if(data_pasien[i].poli == 1 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false ){//CHECK POLI DAN STATUS PEMERIKSAAN
                    system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PEMERIKSAAN---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien[i].umur;
            cout<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl<<endl;
    cout<<"TENSI          : ";
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].tensi;
    cout<<endl;
    cout<<"BERAT BADAN    : ";
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].berat_badan;
    cout<<endl;
    cout<<"TINGGI BADAN   : ";
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].tinggi_badan;
    cout<<endl;
    cout<<"HASIL          : ";
    cin.ignore();
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].hasil;
    cout<<endl;
    cout<<"JUMLAH OBAT    : ";
    cin>>banyak_obat;cout<<endl;
    for(int l=0; l<banyak_obat; l++)
    {
        cout<<"KODE OBAT      : ";
        cin>>kode_obat1;
        for(int k=0;k<jml_obat;k++){
            if(data_obat[k].kode_obat==kode_obat1)
        cout<<endl;
        cout<<"NAMA OBAT      : "<<data_obat[k].nama_obat;
        data_pasien[i].data_pemeriksaan[l].nama_obat=data_obat[k].nama_obat;
        cout<<endl<<endl;
        cout<<"KALI MINUM/hr  : ";
        cin>>data_pasien[i].data_pemeriksaan[l].kali_minum;
        cout<<endl;
        cout<<"ATURAN MINUM   : 1. SEBELUM MAKAN\n";
        cout<<"                 2. SAAT MAKAN\n";
        cout<<"                 3. SESUDAH MAKAN\n";
        cin>>data_pasien[i].data_pemeriksaan[l].aturan_minum;
        cout<<endl;
                total=data_obat[k].harga+total;
                data_pasien[i].biaya=total;
                if(registration_menu==2)
                {
                data_pasien[i].biaya + 2000;
                }

        }
    data_pasien[i].data_pemeriksaan[sv_ao].nama_obat=data_pasien[i].data_pemeriksaan[l].nama_obat;
    data_pasien[i].data_pemeriksaan[sv_ao].kali_minum=data_pasien[i].data_pemeriksaan[l].kali_minum;
    data_pasien[i].data_pemeriksaan[sv_ao].aturan_minum=data_pasien[i].data_pemeriksaan[l].aturan_minum;
    sv_ao++;
    }
    cout<<"TEKAN SPACE UNTUK PRINT HASIL PEMERIKSAAN\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_SPACE))
    {
        system("CLS");
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---HASIL PEMERIKSAAN---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
        cout<<endl<<endl;
        cout<<"NAMA           : "<<data_pasien[i].nama;
        cout<<endl<<endl;
        cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
        cout<<endl<<endl;
        cout<<"UMUR           : "<<data_pasien[i].umur;
        cout<<endl<<endl;
        cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
        cout<<endl<<endl;
        cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
        cout<<endl<<endl;
        cout<<"TENSI          : "<<data_pasien[i].data_pemeriksaan[sv_dp].tensi<<endl<<endl;
        cout<<"BERAT BADAN    : "<<data_pasien[i].data_pemeriksaan[sv_dp].berat_badan<<endl<<endl;
        cout<<"TINGGI BADAN   : "<<data_pasien[i].data_pemeriksaan[sv_dp].tinggi_badan<<endl<<endl;
        cout<<"HASIL          : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl<<endl;
        for(int j=0; j<banyak_obat; j++)
        {
                cout<<"OBAT "<<data_pasien[i].data_pemeriksaan[j].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" DALAM 1 HARI "<< data_pasien[i].data_pemeriksaan[j].aturan_minum<<endl<<endl;

            }
        cout<<"             TEKAN ESCAPE UNTUK KEMBALI\n\n";
    }
    data_pasien[i].status_pemeriksaan=true;
    data_pasien[i].status_pembayaran=false;
    data_pasien[i].status_pengambilan=false;
    jml_antrian_umum++;
    no_antrian_umum++;
    sv_dp++;
    system("PAUSE>NUL");
        system("CLS");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        main();
    }
    else{
        main();
    }

                }
                else if(data_pasien[i].poli!=1 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false){
            cout<<"                              TERDAPAT KESALAHAN\n";
            cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TIDAK TERDAFTAR DI POLI UMUM\n\n";
            cout<<"                         UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                      UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_umum();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_umum();

            }

                }
                //CHECK STATUS PEMERIKSAAN
                else if(data_pasien[i].status_pemeriksaan==true && data_pasien[i].poli==1){
                cout<<"                              TERDAPAT KESALAHAN\n";
                cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TELAH DIPERIKSA DI POLI UMUM\n\n";
                cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
                cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_umum();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_umum();

            }
        }
        }//PENGECEKAN NO_REKAM MEDIS
        else
        {
            system("CLS");
            gotoxy(67,28);cout<<"   DATA YANG ANDA CARI TIDAK DITEMUKAN\n";
            gotoxy(67,29);cout<<"    UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            gotoxy(67,23);cout<<" UNTUK KEMBALI KE MENU  UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_umum();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_umum();

            }
        }
    }

    }
void pemeriksaan_poli_gigi()
{
    gotoxy(77,24);
    cout<<" ---POLI GIGI---";
    gotoxy(77,25);
    cout<<"NOMOR REKAM MEDIS";
    gotoxy(77,26);
    cout<<"       ";
    cin>>no_rekam_medis;
    int total=0;
    for(int i=0;i<jml_pasien;i++){
            if(data_pasien[i].NRM==no_rekam_medis){
                if(data_pasien[i].poli == 2 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false ){//CHECK POLI DAN STATUS PEMERIKSAAN
                    system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PEMERIKSAAN---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien[i].umur;
            cout<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl<<endl;
    cout<<"HASIL          : ";
    cin.ignore();
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].hasil;
    cout<<endl;
    cout<<"JUMLAH OBAT    : ";
    cin>>banyak_obat;cout<<endl;
    for(int l=0; l<banyak_obat; l++)
    {
        cout<<"KODE OBAT      : ";
        cin>>kode_obat1;
        for(int k=0;k<jml_obat;k++){
            if(data_obat[k].kode_obat==kode_obat1)
        cout<<endl;
        cout<<"NAMA OBAT      : "<<data_obat[k].nama_obat;
        data_pasien[i].data_pemeriksaan[l].nama_obat=data_obat[k].nama_obat;
        cout<<endl<<endl;
        cout<<"KALI MINUM/hr  : ";
        cin>>data_pasien[i].data_pemeriksaan[l].kali_minum;
        cout<<endl;
        cout<<"ATURAN MINUM   : 1. SEBELUM MAKAN\n";
        cout<<"                 2. SAAT MAKAN\n";
        cout<<"                 3. SESUDAH MAKAN\n";
        cin>>data_pasien[i].data_pemeriksaan[l].aturan_minum;
        cout<<endl;
                total=data_obat[k].harga+total;
                data_pasien[i].biaya=total;
                if(registration_menu==2)
                {
                data_pasien[i].biaya + 2000;
                }

        }
    data_pasien[i].data_pemeriksaan[sv_ao].nama_obat=data_pasien[i].data_pemeriksaan[l].nama_obat;
    data_pasien[i].data_pemeriksaan[sv_ao].kali_minum=data_pasien[i].data_pemeriksaan[l].kali_minum;
    data_pasien[i].data_pemeriksaan[sv_ao].aturan_minum=data_pasien[i].data_pemeriksaan[l].aturan_minum;
    sv_ao++;
    }
    cout<<"TEKAN SPACE UNTUK PRINT HASIL PEMERIKSAAN\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_SPACE))
    {
        system("CLS");
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---HASIL PEMERIKSAAN---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
        cout<<endl<<endl;
        cout<<"NAMA           : "<<data_pasien[i].nama;
        cout<<endl<<endl;
        cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
        cout<<endl<<endl;
        cout<<"UMUR           : "<<data_pasien[i].umur;
        cout<<endl<<endl;
        cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
        cout<<endl<<endl;
        cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
        cout<<endl<<endl;
        cout<<"HASIL          : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl<<endl;
        for(int j=0; j<banyak_obat; j++)
        {
                cout<<"OBAT "<<data_pasien[i].data_pemeriksaan[j].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" DALAM 1 HARI "<< data_pasien[i].data_pemeriksaan[j].aturan_minum<<endl<<endl;

            }
        cout<<"             TEKAN ESCAPE UNTUK KEMBALI\n\n";
    }
    data_pasien[i].status_pemeriksaan=true;
    data_pasien[i].status_pembayaran=false;
    data_pasien[i].status_pengambilan=false;
    jml_antrian_gigi++;
    no_antrian_gigi++;
    sv_dp++;
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        main();
    }
    else{
        main();
    }

                }
                else if(data_pasien[i].poli!=2 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false){
            system("CLS");
            cout<<"                              TERDAPAT KESALAHAN\n";
            cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TIDAK TERDAFTAR DI POLI GIGI\n\n";
            cout<<"                         UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                      UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_gigi();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_gigi();

            }

                }
                //CHECK STATUS PEMERIKSAAN
                else if(data_pasien[i].status_pemeriksaan==true && data_pasien[i].poli==2){
                cout<<"                              TERDAPAT KESALAHAN\n";
                cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TELAH DIPERIKSA DI POLI UMUM\n\n";
                cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
                cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_gigi();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_gigi();

            }
        }
        }//PENGECEKAN NO_REKAM MEDIS
        else
        {
            cout<<"                           DATA YANG ANDA CARI TIDAK DITEMUKAN\n";
            cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_gigi();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_gigi();

            }
        }
    }
}
void pemeriksaan_poli_mata()
{
    gotoxy(77,24);
    cout<<" ---POLI MATA---";
    gotoxy(77,25);
    cout<<"NOMOR REKAM MEDIS";
    gotoxy(77,26);
    cout<<"       ";
    cin>>no_rekam_medis;
    int total=0;
    for(int i=0;i<jml_pasien;i++){
            if(data_pasien[i].NRM==no_rekam_medis){
                if(data_pasien[i].poli == 3 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false ){//CHECK POLI DAN STATUS PEMERIKSAAN
                    system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PEMERIKSAAN---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien[i].umur;
            cout<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl<<endl;
    cout<<"HASIL          : ";
    cin.ignore();
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].hasil;
    cout<<endl;
    cout<<"JUMLAH OBAT    : ";
    cin>>banyak_obat;cout<<endl;
    for(int l=0; l<banyak_obat; l++)
    {
        cout<<"KODE OBAT      : ";
        cin>>kode_obat1;
        for(int k=0;k<jml_obat;k++){
            if(data_obat[k].kode_obat==kode_obat1)
        cout<<endl;
        cout<<"NAMA OBAT      : "<<data_obat[k].nama_obat;
        data_pasien[i].data_pemeriksaan[l].nama_obat=data_obat[k].nama_obat;
        cout<<endl<<endl;
        cout<<"KALI MINUM/hr  : ";
        cin>>data_pasien[i].data_pemeriksaan[l].kali_minum;
        cout<<endl;
        cout<<"ATURAN MINUM   : 1. SEBELUM MAKAN\n";
        cout<<"                 2. SAAT MAKAN\n";
        cout<<"                 3. SESUDAH MAKAN\n";
        cin>>data_pasien[i].data_pemeriksaan[l].aturan_minum;
        cout<<endl;
                total=data_obat[k].harga+total;
                data_pasien[i].biaya=total;
                if(registration_menu==2)
                {
                data_pasien[i].biaya + 2000;
                }

        }
    data_pasien[i].data_pemeriksaan[sv_ao].nama_obat=data_pasien[i].data_pemeriksaan[l].nama_obat;
    data_pasien[i].data_pemeriksaan[sv_ao].kali_minum=data_pasien[i].data_pemeriksaan[l].kali_minum;
    data_pasien[i].data_pemeriksaan[sv_ao].aturan_minum=data_pasien[i].data_pemeriksaan[l].aturan_minum;
    sv_ao++;
    }
    cout<<"TEKAN SPACE UNTUK PRINT HASIL PEMERIKSAAN\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_SPACE))
    {
        system("CLS");
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---HASIL PEMERIKSAAN---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
        cout<<endl<<endl;
        cout<<"NAMA           : "<<data_pasien[i].nama;
        cout<<endl<<endl;
        cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
        cout<<endl<<endl;
        cout<<"UMUR           : "<<data_pasien[i].umur;
        cout<<endl<<endl;
        cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
        cout<<endl<<endl;
        cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
        cout<<endl<<endl;
        cout<<"HASIL          : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl<<endl;
        for(int j=0; j<banyak_obat; j++)
        {
                cout<<"OBAT "<<data_pasien[i].data_pemeriksaan[j].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" DALAM 1 HARI "<< data_pasien[i].data_pemeriksaan[j].aturan_minum<<endl<<endl;

            }
        cout<<"             TEKAN ESCAPE UNTUK KEMBALI\n\n";
    }
    data_pasien[i].status_pemeriksaan=true;
    data_pasien[i].status_pembayaran=false;
    data_pasien[i].status_pengambilan=false;
    jml_antrian_mata++;
    no_antrian_mata++;
    sv_dp++;
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        main();
    }
    else{
        main();
    }

                }
                else if(data_pasien[i].poli!=3 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false){
            system("CLS");
            cout<<"                              TERDAPAT KESALAHAN\n";
            cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TIDAK TERDAFTAR DI POLI MATA\n\n";
            cout<<"                         UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                      UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_mata();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_mata();

            }

                }
                //CHECK STATUS PEMERIKSAAN
                else if(data_pasien[i].status_pemeriksaan==true && data_pasien[i].poli==3){
                cout<<"                              TERDAPAT KESALAHAN\n";
                cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TELAH DIPERIKSA DI POLI UMUM\n\n";
                cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
                cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_mata();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_mata();

            }
        }
        }//PENGECEKAN NO_REKAM MEDIS
        else
        {
            cout<<"                           DATA YANG ANDA CARI TIDAK DITEMUKAN\n";
            cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_mata();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_mata();

            }
        }
    }
}
void pemeriksaan_poli_anak()
{
    gotoxy(77,24);
    cout<<" ---POLI ANAK---";
    gotoxy(77,25);
    cout<<"NOMOR REKAM MEDIS";
    gotoxy(77,26);
    cout<<"       ";
    cin>>no_rekam_medis;
    int total=0;
    for(int i=0;i<jml_pasien;i++){
            if(data_pasien[i].NRM==no_rekam_medis){
                if(data_pasien[i].poli == 4 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false ){//CHECK POLI DAN STATUS PEMERIKSAAN
                    system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PEMERIKSAAN---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien[i].umur;
            cout<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl<<endl;
    cout<<"HASIL          : ";
    cin.ignore();
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].hasil;
    cout<<endl;
    cout<<"JUMLAH OBAT    : ";
    cin>>banyak_obat;cout<<endl;
    for(int l=0; l<banyak_obat; l++)
    {
        cout<<"KODE OBAT      : ";
        cin>>kode_obat1;
        for(int k=0;k<jml_obat;k++){
            if(data_obat[k].kode_obat==kode_obat1)
        cout<<endl;
        cout<<"NAMA OBAT      : "<<data_obat[k].nama_obat;
        data_pasien[i].data_pemeriksaan[l].nama_obat=data_obat[k].nama_obat;
        cout<<endl<<endl;
        cout<<"KALI MINUM/hr  : ";
        cin>>data_pasien[i].data_pemeriksaan[l].kali_minum;
        cout<<endl;
        cout<<"ATURAN MINUM   : 1. SEBELUM MAKAN\n";
        cout<<"                 2. SAAT MAKAN\n";
        cout<<"                 3. SESUDAH MAKAN\n";
        cin>>data_pasien[i].data_pemeriksaan[l].aturan_minum;
        cout<<endl;
                total=data_obat[k].harga+total;
                data_pasien[i].biaya=total;
                if(registration_menu==2)
                {
                data_pasien[i].biaya + 2000;
                }

        }
    data_pasien[i].data_pemeriksaan[sv_ao].nama_obat=data_pasien[i].data_pemeriksaan[l].nama_obat;
    data_pasien[i].data_pemeriksaan[sv_ao].kali_minum=data_pasien[i].data_pemeriksaan[l].kali_minum;
    data_pasien[i].data_pemeriksaan[sv_ao].aturan_minum=data_pasien[i].data_pemeriksaan[l].aturan_minum;
    sv_ao++;
    }
    cout<<"TEKAN SPACE UNTUK PRINT HASIL PEMERIKSAAN\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_SPACE))
    {
        system("CLS");
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---HASIL PEMERIKSAAN---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
        cout<<endl<<endl;
        cout<<"NAMA           : "<<data_pasien[i].nama;
        cout<<endl<<endl;
        cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
        cout<<endl<<endl;
        cout<<"UMUR           : "<<data_pasien[i].umur;
        cout<<endl<<endl;
        cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
        cout<<endl<<endl;
        cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
        cout<<endl<<endl;
        cout<<"HASIL          : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl<<endl;
        for(int j=0; j<banyak_obat; j++)
        {
                cout<<"OBAT "<<data_pasien[i].data_pemeriksaan[j].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" DALAM 1 HARI "<< data_pasien[i].data_pemeriksaan[j].aturan_minum<<endl<<endl;

            }
        cout<<"             TEKAN ESCAPE UNTUK KEMBALI\n\n";
    }
    data_pasien[i].status_pemeriksaan=true;
    data_pasien[i].status_pembayaran=false;
    data_pasien[i].status_pengambilan=false;
    jml_antrian_anak++;
    no_antrian_anak++;
    sv_dp++;
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        main();
    }
    else{
        main();
    }

                }
                else if(data_pasien[i].poli!=4 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false){
            system("CLS");
            cout<<"                              TERDAPAT KESALAHAN\n";
            cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TIDAK TERDAFTAR DI POLI ANAK\n\n";
            cout<<"                         UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                      UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_anak();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_anak();

            }

                }
                //CHECK STATUS PEMERIKSAAN
                else if(data_pasien[i].status_pemeriksaan==true && data_pasien[i].poli==4){
                cout<<"                              TERDAPAT KESALAHAN\n";
                cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TELAH DIPERIKSA DI POLI UMUM\n\n";
                cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
                cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_anak();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_anak();

            }
        }
        }//PENGECEKAN NO_REKAM MEDIS
        else
        {
            cout<<"                           DATA YANG ANDA CARI TIDAK DITEMUKAN\n";
            cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_anak();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_anak();

            }
        }
    }
}
void pemeriksaan_poli_syaraf()
{
    gotoxy(77,24);
    cout<<" ---POLI SYARAF---";
    gotoxy(77,25);
    cout<<"NOMOR REKAM MEDIS";
    gotoxy(77,26);
    cout<<"       ";
    cin>>no_rekam_medis;
    int total=0;
    for(int i=0;i<jml_pasien;i++){
            if(data_pasien[i].NRM==no_rekam_medis){
                if(data_pasien[i].poli == 5 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false ){//CHECK POLI DAN STATUS PEMERIKSAAN
                    system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PEMERIKSAAN---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien[i].umur;
            cout<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl<<endl;
    cout<<"HASIL          : ";
    cin.ignore();
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].hasil;
    cout<<endl;
    cout<<"JUMLAH OBAT    : ";
    cin>>banyak_obat;cout<<endl;
    for(int l=0; l<banyak_obat; l++)
    {
        cout<<"KODE OBAT      : ";
        cin>>kode_obat1;
        for(int k=0;k<jml_obat;k++){
            if(data_obat[k].kode_obat==kode_obat1)
        cout<<endl;
        cout<<"NAMA OBAT      : "<<data_obat[k].nama_obat;
        data_pasien[i].data_pemeriksaan[l].nama_obat=data_obat[k].nama_obat;
        cout<<endl<<endl;
        cout<<"KALI MINUM/hr  : ";
        cin>>data_pasien[i].data_pemeriksaan[l].kali_minum;
        cout<<endl;
        cout<<"ATURAN MINUM   : 1. SEBELUM MAKAN\n";
        cout<<"                 2. SAAT MAKAN\n";
        cout<<"                 3. SESUDAH MAKAN\n";
        cin>>data_pasien[i].data_pemeriksaan[l].aturan_minum;
        cout<<endl;
                total=data_obat[k].harga+total;
                data_pasien[i].biaya=total;
                if(registration_menu==2)
                {
                data_pasien[i].biaya + 2000;
                }

        }
    data_pasien[i].data_pemeriksaan[sv_ao].nama_obat=data_pasien[i].data_pemeriksaan[l].nama_obat;
    data_pasien[i].data_pemeriksaan[sv_ao].kali_minum=data_pasien[i].data_pemeriksaan[l].kali_minum;
    data_pasien[i].data_pemeriksaan[sv_ao].aturan_minum=data_pasien[i].data_pemeriksaan[l].aturan_minum;
    sv_ao++;
    }
    cout<<"TEKAN SPACE UNTUK PRINT HASIL PEMERIKSAAN\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_SPACE))
    {
        system("CLS");
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---HASIL PEMERIKSAAN---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
        cout<<endl<<endl;
        cout<<"NAMA           : "<<data_pasien[i].nama;
        cout<<endl<<endl;
        cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
        cout<<endl<<endl;
        cout<<"UMUR           : "<<data_pasien[i].umur;
        cout<<endl<<endl;
        cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
        cout<<endl<<endl;
        cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
        cout<<endl<<endl;
        cout<<"HASIL          : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl<<endl;
        for(int j=0; j<banyak_obat; j++)
        {
                cout<<"OBAT "<<data_pasien[i].data_pemeriksaan[j].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" DALAM 1 HARI "<< data_pasien[i].data_pemeriksaan[j].aturan_minum<<endl<<endl;

            }
        cout<<"             TEKAN ESCAPE UNTUK KEMBALI\n\n";
    }
    data_pasien[i].status_pemeriksaan=true;
    data_pasien[i].status_pembayaran=false;
    data_pasien[i].status_pengambilan=false;
    jml_antrian_gigi++;
    no_antrian_gigi++;
    sv_dp++;
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        main();
    }
    else{
        main();
    }

                }
                else if(data_pasien[i].poli!=5 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false){
            system("CLS");
            cout<<"                              TERDAPAT KESALAHAN\n";
            cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TIDAK TERDAFTAR DI POLI SYARAF\n\n";
            cout<<"                         UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                      UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_syaraf();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_syaraf();

            }

                }
                //CHECK STATUS PEMERIKSAAN
                else if(data_pasien[i].status_pemeriksaan==true && data_pasien[i].poli==5){
                cout<<"                              TERDAPAT KESALAHAN\n";
                cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TELAH DIPERIKSA DI POLI UMUM\n\n";
                cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
                cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_syaraf();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_syaraf();

            }
        }
        }//PENGECEKAN NO_REKAM MEDIS
        else
        {
            cout<<"                           DATA YANG ANDA CARI TIDAK DITEMUKAN\n";
            cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_syaraf();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_syaraf();

            }
        }
    }
}
void pemeriksaan_poli_kandungan()
{
    gotoxy(77,24);
    cout<<" ---POLI KANDUNGAN---";
    gotoxy(77,25);
    cout<<"NOMOR REKAM MEDIS";
    gotoxy(77,26);
    cout<<"       ";
    cin>>no_rekam_medis;
    int total=0;
    for(int i=0;i<jml_pasien;i++){
            if(data_pasien[i].NRM==no_rekam_medis){
                if(data_pasien[i].poli == 6 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false ){//CHECK POLI DAN STATUS PEMERIKSAAN
                    system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                     ---PEMERIKSAAN---                  |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"UMUR           : "<<data_pasien[i].umur;
            cout<<endl<<endl;
            cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl<<endl;
            cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl<<endl;
    cout<<"HASIL          : ";
    cin.ignore();
    cin>>data_pasien[i].data_pemeriksaan[sv_dp].hasil;
    cout<<endl;
    cout<<"JUMLAH OBAT    : ";
    cin>>banyak_obat;cout<<endl;
    for(int l=0; l<banyak_obat; l++)
    {
        cout<<"KODE OBAT      : ";
        cin>>kode_obat1;
        for(int k=0;k<jml_obat;k++){
            if(data_obat[k].kode_obat==kode_obat1)
        cout<<endl;
        cout<<"NAMA OBAT      : "<<data_obat[k].nama_obat;
        data_pasien[i].data_pemeriksaan[l].nama_obat=data_obat[k].nama_obat;
        cout<<endl<<endl;
        cout<<"KALI MINUM/hr  : ";
        cin>>data_pasien[i].data_pemeriksaan[l].kali_minum;
        cout<<endl;
        cout<<"ATURAN MINUM   : 1. SEBELUM MAKAN\n";
        cout<<"                 2. SAAT MAKAN\n";
        cout<<"                 3. SESUDAH MAKAN\n";
        cin>>data_pasien[i].data_pemeriksaan[l].aturan_minum;
        cout<<endl;
                total=data_obat[k].harga+total;
                data_pasien[i].biaya=total;
                if(registration_menu==2)
                {
                data_pasien[i].biaya + 2000;
                }

        }
    data_pasien[i].data_pemeriksaan[sv_ao].nama_obat=data_pasien[i].data_pemeriksaan[l].nama_obat;
    data_pasien[i].data_pemeriksaan[sv_ao].kali_minum=data_pasien[i].data_pemeriksaan[l].kali_minum;
    data_pasien[i].data_pemeriksaan[sv_ao].aturan_minum=data_pasien[i].data_pemeriksaan[l].aturan_minum;
    sv_ao++;
    }
    cout<<"TEKAN SPACE UNTUK PRINT HASIL PEMERIKSAAN\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_SPACE))
    {
        system("CLS");
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---HASIL PEMERIKSAAN---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
        cout<<endl<<endl;
        cout<<"NAMA           : "<<data_pasien[i].nama;
        cout<<endl<<endl;
        cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
        cout<<endl<<endl;
        cout<<"UMUR           : "<<data_pasien[i].umur;
        cout<<endl<<endl;
        cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
        cout<<endl<<endl;
        cout<<"KELUHAN        : "<<data_pasien[i].keluhan;
        cout<<endl<<endl;
        cout<<"HASIL          : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl<<endl;
        for(int j=0; j<banyak_obat; j++)
        {
                cout<<"OBAT "<<data_pasien[i].data_pemeriksaan[j].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" DALAM 1 HARI "<< data_pasien[i].data_pemeriksaan[j].aturan_minum<<endl<<endl;

            }
        cout<<"             TEKAN ESCAPE UNTUK KEMBALI\n\n";
    }
    data_pasien[i].status_pemeriksaan=true;
    data_pasien[i].status_pembayaran=false;
    data_pasien[i].status_pengambilan=false;
    jml_antrian_kandungan++;
    no_antrian_kandungan++;
    sv_dp++;
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        main();
    }
    else{
        main();
    }

                }
                else if(data_pasien[i].poli!=6 && data_pasien[i].status_pemeriksaan== false && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false){
            system("CLS");
            cout<<"                              TERDAPAT KESALAHAN\n";
            cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TIDAK TERDAFTAR DI POLI KANDUNGAN\n\n";
            cout<<"                         UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                      UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_kandungan();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_kandungan();

            }

                }
                //CHECK STATUS PEMERIKSAAN
                else if(data_pasien[i].status_pemeriksaan==true && data_pasien[i].poli==6){
                cout<<"                              TERDAPAT KESALAHAN\n";
                cout<<"PASIEN DENGAN NO REKAM MEDIS "<<data_pasien[i].NRM<<" TELAH DIPERIKSA DI POLI UMUM\n\n";
                cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
                cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_kandungan();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_kandungan();

            }
        }
        }//PENGECEKAN NO_REKAM MEDIS
        else
        {
            cout<<"                           DATA YANG ANDA CARI TIDAK DITEMUKAN\n";
            cout<<"                           UNTUK MEMASSUKAN ULANG  TEKAN SPACE\n";
            cout<<"                        UNTUK KEMBALI KE MENU UTAMA TEKAN ESCAPE\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                pemeriksaan_poli_kandungan();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else
            {
                system("CLS");
                pemeriksaan_poli_kandungan();

            }
        }
    }
}
void kasir()
{
    //DEKLARASI
    int uang=0,kembalian=0;
    //SOURCE CODE
    if(jml_pasien==0 || jml_karyawan == 0){
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                         ---KASIR---                    |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,18);cout<<"   MENU KASIR BELUM DAPAT DI AKSES\n\n";
              if(data_pasien[0].status_pemeriksaan==false){
        gotoxy(62,20);cout<<"SISTEM MENDETEKSI BELUM TERDAPAT PASIEN DIPERIKSA\n\n";
        }
        if(jml_karyawan==0){
        gotoxy(61,21);cout<<"SISTEM  MENDETEKSI BELUM TERDAPAT KARYAWAN TERDAFTAR\n\n";
        }
        gotoxy(72,25);
        system("PAUSE");
        system("CLS");

    }
    else{
    gotoxy(77,25);
    cout<<"No.REK MEDIS : ";
    gotoxy(82,26);
    cin>>no_rekam_medis;
    system("CLS");
    for(int i=0; i<jml_pasien; i++)
    {
        if(data_pasien[i].NRM == no_rekam_medis && data_pasien[i].status_pemeriksaan== true && data_pasien[i].status_pembayaran==false && data_pasien[i].status_pengambilan==false)
        {
            if(data_pasien[i].biaya==0){
                                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                   ---KASIR RUMAH SAKIT---              |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"      OBAT UNTUK PASIEN TIDAK TERSEDIA DI RUMAH SAKIT\n\n";
            cout<<"                 TEKAN ESCAPE UNTUK KEMBALI\n";
            system("PAUSE>NUL");
            system("CLS");
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
                data_pasien[i].status_pembayaran=true;
            }
            else{
                main();
                data_pasien[i].status_pembayaran=true;
            }
            }
            else
            system("CLS");
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                   ---KASIR RUMAH SAKIT---              |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl<<endl;
            cout<<"NAMA           : "<<data_pasien[i].nama;
            cout<<endl<<endl;
            cout<<"PEMBAYARAN     : "<<data_pasien[i].biaya;
            cout<<endl<<endl;
            cout<<setw(60)<<setfill('=')<<"\n";
            cout<<"UANG           : ";
            cin>>uang;
            cout<<endl;
            cout<<"TOTAL          : "<<data_pasien[i].biaya<<endl<<endl;
            kembalian = uang - data_pasien[i].biaya;
            cout<<"KEMBALIAN      : "<<kembalian<<endl<<endl;
            cout<<"             TEKAN SPACE JIKA PEMBAYARAN TELAH LUNAS\n\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_SPACE) && kembalian >= 0){
                data_pasien[i].status_pembayaran = true;
                main();
            }
            else{
                data_pasien[i].status_pembayaran = true;
                main();
            }
            system("CLS");
        }
        else if(data_pasien[i].NRM != no_rekam_medis)
        {
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                   ---KASIR RUMAH SAKIT---              |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"             NOMOR REKAM MEDIS TIDAK DITEMUKAN!!!\n\n";
            cout<<"      TEKAN SPACE UNTUK MEMASSUKAN ULANG NO REKAM MEDIS\n";
            cout<<"                 TEKAN ESCAPE UNTUK KEMBALI\n";
            system("PAUSE>NUL");
            system("CLS");
            if(GetAsyncKeyState(VK_SPACE))
            {
                system("CLS");
                kasir();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                system("CLS");
                main();
            }
            else{
                system("CLS");
                kasir();
            }
        }
        else if(data_pasien[i].status_pembayaran==true){
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                   ---KASIR RUMAH SAKIT---              |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"               PEMBAYARAN TELAH TERSELESAIKAN!!!\n\n";
            cout<<"                  TEKAN ESCAPE UNTUK KEMBALI\n";
            system("PAUSE>NUL");
            system("CLS");
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
            }
            else{
                main();
            }
        }
    }

    }
}
void apoteker()
{
    if(jml_pasien==0 || jml_karyawan == 0 ){
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                        ---APOTEKER---                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,18);cout<<" MENU APOTEKER BELUM DAPAT DI AKSES\n\n";
        if(data_pasien[0].status_pembayaran==false){
        gotoxy(56,20);cout<<"SISTEM MENDETEKSI  BELUM TERDAPAT PASIEN MELAKUKAN PEMBAYARAN\n\n";
        }
        if(jml_karyawan==0){
        gotoxy(61,21);cout<<"SISTEM MENDETEKSI BELUM TERDAPAT KARYAWAN TERDAFTAR\n\n";
        }
        gotoxy(72,25);
        system("PAUSE");
        system("CLS");

    }
    else{
            gotoxy(77,25);
    cout<<"No.REK MEDIS : ";
    gotoxy(82,26);
    cin>>no_rekam_medis;
    system("CLS");
    for(int i=0; i<jml_pasien; i++)
    {
        i=j;
        if(data_pasien[i].NRM==no_rekam_medis)
        {
            if(data_pasien[i].status_pemeriksaan== true && data_pasien[i].status_pembayaran == true && data_pasien[i].status_pengambilan==true){
                            gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                        ---APOTEKER---                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,18);
        cout<<"PEMERIKSAAN PASIEN ATAS NAMA "<<data_pasien[i].nama<<" TELAH SELESAI\n";
        gotoxy(57,19);
        cout<<"                           TERIMA KASIH\n\n";
        gotoxy(72,23);system("PAUSE");

            }
            else if(data_pasien[i].status_pemeriksaan== true && data_pasien[i].status_pembayaran == true && data_pasien[i].status_pengambilan==false){
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"No.REK MEDIS\t\t"<<data_pasien[i].NRM;
            cout<<"            \t\t"<<data_pasien[i].nama<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<endl;
            for (int k=0;k<banyak_obat;k++){
                for(int l=0; l<jml_obat; l++)
            {
                data_pasien[i].data_pemeriksaan[j].aturan_minum==aturan_minum_obat;
                if(aturan_minum_obat==1){
                    cout<<" SEBELUM MAKAN\n\n";
                }
                else if(aturan_minum_obat==2){
                    cout<<" SAAT MAKAN\n\n";
                }
                else if(aturan_minum_obat==3){
                    cout<<" SETELAH MAKAN\n\n";
                }
                cout<<"NAMA OBAT "<<l+1<<"   : "<<data_obat[l].nama_obat<<" DIMINUM "<<data_pasien[i].data_pemeriksaan[j].kali_minum<<" KALI DALAM 1 HARI "<<aturan_minum_obat<<endl<<endl;

            }
            }
            data_pasien[i].status_pengambilan=true;
            system("PAUSE");
            system("CLS");
            }
            else if(data_pasien[i].status_pemeriksaan== true && data_pasien[i].status_pembayaran == false  && data_pasien[i].status_pengambilan == false){
            cout<<"               PEMBAYARAN BELUM TERSELESAIKAN!!!\n\n";
            cout<<"      TEKAN SPACE UNTUK MEMASSUKAN ULANG NO REKAM MEDIS\n";
            cout<<"                 TEKAN ESCAPE UNTUK KEMBALI\n";
            system("PAUSE>NUL");
            system("CLS");
            if(GetAsyncKeyState(VK_SPACE))
            {
                apoteker();
            }
            if(GetAsyncKeyState(VK_ESCAPE)){
                main();
            }
            else{
                main();
            }

            }
        }
        else if(data_pasien[i].NRM!=no_rekam_medis)
        {
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                   ---KASIR RUMAH SAKIT---              |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"             NOMOR REKAM MEDIS TIDAK DITEMUKAN!!!\n\n";
            cout<<"      TEKAN SPACE UNTUK MEMASSUKAN ULANG NO REKAM MEDIS\n";
            cout<<"                 TEKAN ESCAPE UNTUK KEMBALI\n";
            system("PAUSE>NUL");
            system("CLS");
            if(GetAsyncKeyState(VK_SPACE))
            {
                kasir();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
            }
     }
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////M E N U     A D M I N///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void admin()
{

    system("CLS");
    bool running=true;
    int menu_admin=1;
    gotoxy(54,14);
    cout<<"-->";
    int x=14;
    while(running)
    {
        running=true;
        gotoxy(57,9);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,10);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,11);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,12);
        cout<<"|                        KHUSUS ADMIN                    |\n";
        gotoxy(57,13);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,14);
        cout<<"| PENDAFTARAN DOKTER                                     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"| PENDAFTARAN KARYAWAN                                   |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,18);
        cout<<"| PENDAFTARAN OBAT                                       |\n";
        gotoxy(57,19);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,20);
        cout<<"| EDIT DATA                                              |\n";
        gotoxy(57,21);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,22);
        cout<<"| HAPUS DATA                                             |\n";
        gotoxy(57,23);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,24);
        cout<<"| TAMPILKAN DATA                                         |\n";
        gotoxy(57,25);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,26);
        cout<<"| LOGIN                                                  |\n";
        gotoxy(57,27);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        PlaySound(TEXT("pilih_menu.wav"), NULL, SND_SYNC);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_UP))
        {
            gotoxy(54,x);
            cout<<"   ";
            x-=2;
            if(x<14)
            {
                x=26;
                gotoxy(54,26);
                cout<<"-->";
                menu_admin=7;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                menu_admin--;
                continue;
            }
        }

        if(GetAsyncKeyState(VK_DOWN))
        {
            gotoxy(54,x);
            cout<<"   ";
            x+=2;
            if(x>26)
            {
                x=26;
                gotoxy(54,26);
                cout<<"-->";
                menu_admin=7;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                menu_admin++;
                continue;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            main();
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            switch(menu_admin)
            {
//PILIHAN MENU UTAMA
            case 1:
            {
                running=false;
                system("CLS");
                pendaftaran_dokter();
                break;
            }
            case 2:
            {
                running=false;
                system("CLS");
                pendaftaran_karyawan();
                break;
            }
            case 3:
            {
                running=false;
                system("CLS");
                pendaftaran_obat();
                break;
            }
            case 4:
            {
                running=false;
                system("CLS");
                edit_data();
                break;
            }
            case 5:
            {
                running=false;
                system("CLS");
                //HAPUS();
                break;

            }
            case 6:
            {
                running=false;
                system("CLS");
                tampilkan_data();
                break;
            }
            case 7:{
                running=false;
                system("CLS");
                login_dokter();
                break;

            }

            }
        }
    }
}
//EDIT DATA
void edit_data()
{
        if(jml_obat==0 || jml_pasien==0 || jml_karyawan == 0){
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                      ---EDIT DATA---                   |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,18);cout<<"MENU EDIT DATA BELUM DAPAT DI AKSES\n\n";
        gotoxy(72,23);system("PAUSE");
        system("CLS");

    }
    else{
         int x=14,menu_edit=1;
    gotoxy(54,14);
    cout<<"-->";
    running=true;
    while(running)
    {
        gotoxy(57,7);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,8);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,9);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,10);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|                      ---EDIT DATA---                   |\n";
        gotoxy(57,13);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,14);
        cout<<"| DOKTER                                                 |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"| KARYAWAN                                               |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,18);
        cout<<"| OBAT                                                   |\n";
        gotoxy(57,19);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,20);
        cout<<"| PASIEN                                                 |\n";
        gotoxy(57,21);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        PlaySound(TEXT("pilih_menu.wav"), NULL, SND_SYNC);
        system("PAUSE>NUL");
        system("CLS");
        if((GetAsyncKeyState(VK_UP) && x >13) || x==14)
        {
            gotoxy(54,x);
            cout<<"   ";
            x-=2;
            if(x<14 || x==14)
            {
                gotoxy(54,14);
                cout<<"-->";
                x=14;
                menu_edit=1;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                menu_edit--;
                continue;
            }
        }

        if(GetAsyncKeyState(VK_DOWN) && x < 21)
        {
            gotoxy(54,x);
            cout<<"   ";
            x+=2;
            if(x>20)
            {
                gotoxy(54,20);
                cout<<"-->";
                x=20;
                menu_edit=1;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                menu_edit++;
                continue;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            main();
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            switch(menu_edit)
            {

//PILIHAN MENU UTAMA
            case 1:
            {
                running=false;
                system("CLS");
                edit_data_dokter();
                break;
            }
            case 2:
            {
                running=false;
                system("CLS");
                edit_data_karyawan();
                break;
            }
            case 3:
            {
                running=false;
                system("CLS");
                edit_data_obat();
                break;
            }
            case 4:
            {
                running=false;
                system("CLS");
                edit_data_pasien();
                break;
            }
            }
        }
    }
    }
}
void pendaftaran_dokter()
{
    system("CLS");
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                  ---PENDAFTARAN DOKTER---              |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID DOKTER      : ";
    cin>>data_dokter_sementara.ID;
    cout<<endl;
    cout<<"PASSWORD       : ";
    cin>>data_dokter_sementara.password;
    cout<<endl;
    cout<<"NAMA           : ";
    cin.ignore();
    getline(cin, data_dokter_sementara.nama);
    cout<<endl;
    cout<<"TTL            : ";
    getline(cin, data_dokter_sementara.ttl);
    cout<<endl;
    cout<<"JENIS KELAMIN  : ";
    cin.ignore();
    getline(cin, data_dokter_sementara.jenis_kel);
    cout<<endl;
    cout<<"ALAMAT         : ";
    getline(cin, data_dokter_sementara.alamat);
    cout<<endl;
    cout<<"TELP           : ";
    cin>>data_dokter_sementara.no_telp;
    cout<<endl;
    cout<<"POLI           : 1. UMUM\n\n";
    cout<<"                 2. GIGI\n\n";
    cout<<"                 3. MATA\n\n";
    cout<<"                 4. ANAK\n\n";
    cout<<"                 5. SYARAF\n\n";
    cout<<"                 6. KANDUNGAN\n\n";
    cout<<"POLI DOKTER    : ";
    cin>>data_dokter_sementara.poli;
    cout<<endl;
    pengecekan_poli_dokter();
    pengecekan_id_dokter();
}
void pengecekan_poli_dokter()
{
    do{
    if(data_dokter_sementara.poli > 6 || data_dokter_sementara.poli <1)
    {
        checking==false;
        cout<<endl<<endl;
        cout<<"           MAAF PILIHAN YANG ANDA MASSUKAN TIDAK SESUAI\n\n";
        cout<<"                TEKAN SPACE UNTUK MEMASSUKAN ULANG\n";
        cout<<"          TEKAN SELAIN SPACE UNTUK MEMBATALKAN INPUT DATA\n\n";
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_SPACE))
        {
            cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
            cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
            cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|                  ---PENDAFTARAN DOKTER---              |\n";
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"ID DOKTER      : "<<data_dokter_sementara.ID<<endl<<endl;
            cout<<"NAMA           : "<<data_dokter_sementara.nama<<endl<<endl;
            cout<<"TTL            : "<<data_dokter_sementara.ttl<<endl<<endl;
            cout<<"JENIS KELAMIN  : "<<data_dokter_sementara.jenis_kel<<endl<<endl;
            cout<<"ALAMAT         : "<<data_dokter_sementara.alamat<<endl<<endl;
            cout<<"TELP           : "<<data_dokter_sementara.no_telp<<endl<<endl;
            cout<<"POLI           : 1. UMUM\n\n";
            cout<<"                 2. GIGI\n\n";
            cout<<"                 3. MATA\n\n";
            cout<<"                 4. ANAK\n\n";
            cout<<"                 5. SYARAF\n\n";
            cout<<"                 6. KANDUNGAN\n\n";
            cout<<"POLI DOKTER    : ";
            cin>>data_dokter_sementara.poli;
        }
        else
        {
            cout<<"        INPUT DATA DIBATALKAN\n\n";
            system("PAUSE");
            system("CLS");
            main();
        }
    }
    else{
        checking=true;
    }
    }while(checking==false);
}
void pengecekan_id_dokter()
{
    loading();
    system("CLS");
    if(jml_dokter>0)
    {
        do{
        for(int i=0; i<jml_dokter; i++)
        {
            if(data_dokter[i].ID != data_dokter_sementara.ID)
            {
                checking=true;
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                  ---PENDAFTARAN DOKTER---              |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"                 PENDAFTARAN DOKTER BERHASIL\n\n";
                cout<<"       ANDA HARUS MELAKUKAN LOG IN SEBELUM PEMERIKSAAN\n\n";
                data_dokter[sv_dk].ID = data_dokter_sementara.ID;
                data_dokter[sv_dk].nama = data_dokter_sementara.nama;
                data_dokter[sv_dk].ttl = data_dokter_sementara.ttl;
                data_dokter[sv_dk].jenis_kel = data_dokter_sementara.jenis_kel;
                data_dokter[sv_dk].alamat = data_dokter_sementara.alamat;
                data_dokter[sv_dk].no_telp = data_dokter_sementara.no_telp;
                data_dokter[sv_dk].poli=data_dokter_sementara.poli;
                data_dokter[sv_dk].password=data_dokter_sementara.password;
                data_dokter[sv_dk].status=false;
            }
            if(data_dokter[i].ID == data_dokter_sementara.ID)
            {
                checking=false;
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                  ---PENDAFTARAN DOKTER---              |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"                   PENDAFTARAN DOKTER GAGAL\n\n";
                cout<<"       SILAHKAN MASSUKAN ULANG ID DOKTER YANG BERBEDA\n\n";
                system("PAUSE");
                system("CLS");
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                  ---PENDAFTARAN DOKTER---              |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"NAMA           : "<<data_dokter_sementara.nama<<endl<<endl;
                cout<<"TTL            : "<<data_dokter_sementara.ttl<<endl<<endl;
                cout<<"JENIS KEL      : "<<data_dokter_sementara.jenis_kel<<endl<<endl;
                cout<<"ALAMAT         : "<<data_dokter_sementara.alamat<<endl<<endl;
                cout<<"TELP           : "<<data_dokter_sementara.no_telp<<endl<<endl;
                    if(data_dokter_sementara.poli==1)
                    {
                        cout<<"POLI           : UMUM"<<endl;
                    }
                    else if(data_dokter_sementara.poli==2)
                    {
                        cout<<"POLI           : GIGI"<<endl;
                    }
                    else if(data_dokter_sementara.poli==3)
                    {
                        cout<<"POLI           : MATA"<<endl;
                    }
                    else if(data_dokter_sementara.poli==4)
                    {
                        cout<<"POLI           : ANAK"<<endl;
                    }
                    else if(data_dokter_sementara.poli==5)
                    {
                        cout<<"POLI           : SYARAF"<<endl;
                    }
                    else if(data_dokter_sementara.poli==6)
                    {
                        cout<<"POLI           : KANDUNGAN"<<endl;
                    }
                    cout<<endl;
                cout<<"ID DOKTER      : ";
                cin>>data_dokter_sementara.ID;
                cout<<endl;
                loading();
                system("CLS");
            }
        }
        }while(checking==false);
    }
    else if(jml_dokter==0)
    {
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                  ---PENDAFTARAN DOKTER---              |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"                 PENDAFTARAN DOKTER BERHASIL\n\n";
        cout<<"       ANDA HARUS MELAKUKAN LOG IN SEBELUM PEMERIKSAAN\n\n";
        data_dokter[sv_dk].ID = data_dokter_sementara.ID;
        data_dokter[sv_dk].nama = data_dokter_sementara.nama;
        data_dokter[sv_dk].ttl = data_dokter_sementara.ttl;
        data_dokter[sv_dk].jenis_kel = data_dokter_sementara.jenis_kel;
        data_dokter[sv_dk].alamat = data_dokter_sementara.alamat;
        data_dokter[sv_dk].no_telp = data_dokter_sementara.no_telp;
        data_dokter[sv_dk].poli=data_dokter_sementara.poli;
        data_dokter[sv_dk].password=data_dokter_sementara.password;
        data_dokter[sv_dk].status=false;
    }
    sv_dk++;
    jml_dokter++;
    system("PAUSE");
    system("CLS");
}
void pendaftaran_karyawan()
{
    system("CLS");
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                 ---PENDAFTARAN KARYAWAN---             |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID KARYAWAN    : ";
    cin>>data_karyawan_sementara.ID;
    cout<<endl;
    cout<<"NAMA           : ";
    cin.ignore();
    getline(cin, data_karyawan_sementara.nama);
    cout<<endl;
    cout<<"TTL            : ";
    getline(cin, data_karyawan_sementara.ttl);
    cout<<endl;
    cout<<"JENIS KEL      : ";
    getline(cin, data_karyawan_sementara.jenis_kel);
    cout<<endl;
    cout<<"ALAMAT         : ";
    getline(cin, data_karyawan_sementara.alamat);
    cout<<endl;
    cout<<"TELP           : ";
    cin>>data_karyawan_sementara.no_telp;
    cout<<endl;
    cout<<"DIVISI         : 1. PENDAFTARAN\n\n";
    cout<<"                 2. KASIR\n\n";
    cout<<"                 3. APOTEKER\n\n";
    cout<<"PILIH DIVISI   : ";
    cin>>data_karyawan_sementara.divisi;
    cout<<endl;
    pengecekan_divisi_karyawan();
    pengecekan_id_karyawan();
}
void pengecekan_divisi_karyawan()
{
    do{
    if(data_karyawan_sementara.divisi>3 || data_karyawan_sementara.divisi<1)
    {
        checking=false;
        cout<<" MAAF PILIHAN YANG ANDA MASSUKAN TIDAK SESUAI\n\n";
        cout<<"      TEKAN SPACE UNTUK MEMASSUKAN ULANG\n";
        cout<<"TEKAN SELAIN SPACE UNTUK MEMBATALKAN INPUT DATA\n\n";
        system("PAUSE>NUL");
        system("CLS");
    if(GetAsyncKeyState(VK_SPACE))
    {
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                 ---PENDAFTARAN KARYAWAN---             |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"ID KARYAWAN    : "<<data_karyawan_sementara.ID<<endl<<endl;
        cout<<"NAMA           : "<<data_karyawan_sementara.nama<<endl<<endl;
        cout<<"TTL            : "<<data_karyawan_sementara.ttl<<endl<<endl;
        cout<<"JENIS KEL      : "<<data_karyawan_sementara.jenis_kel<<endl<<endl;
        cout<<"ALAMAT         : "<<data_karyawan_sementara.alamat<<endl<<endl;
        cout<<"TELP           : "<<data_karyawan_sementara.no_telp<<endl<<endl;
        cout<<"DIVISI         : 1. PENDAFTARAN\n\n";
        cout<<"                 2. KASIR\n\n";
        cout<<"                 3. APOTEKER\n\n";
        cin>>data_karyawan_sementara.divisi;
        cout<<endl;
    }
    }
    else{
        checking=true;
    }
    }while(checking==false);
}
void pengecekan_id_karyawan()
{
    loading();
    system("CLS");
    if(jml_karyawan>0)
    {
        do{
        for(int i=0; i<jml_karyawan; i++)
        {
            if(data_karyawan[i].ID != data_karyawan_sementara.ID)
            {
                checking=true;
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                 ---PENDAFTARAN KARYAWAN---             |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"                PENDAFTARAN KARYAWAN BERHASIL\n\n";
                cout<<"         ANDA HARUS MELAKUKAN LOG IN SEBELUM BEKERJA\n\n";
                data_karyawan[sv_ky].ID = data_karyawan_sementara.ID;
                data_karyawan[sv_ky].nama = data_karyawan_sementara.nama;
                data_karyawan[sv_ky].ttl = data_karyawan_sementara.ttl;
                data_karyawan[sv_ky].jenis_kel = data_karyawan_sementara.jenis_kel;
                data_karyawan[sv_ky].alamat = data_karyawan_sementara.alamat;
                data_karyawan[sv_ky].no_telp = data_karyawan_sementara.no_telp;
                data_karyawan[sv_ky].divisi = data_karyawan_sementara.divisi;
            }
            else
            {
                checking=false;
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                 ---PENDAFTARAN KARYAWAN---             |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"                  PENDAFTARAN KARYAWAN GAGAL\n\n";
                cout<<"      SILAHKAN MASSUKAN ULANG ID KARYAWAN YANG BERBEDA\n\n";
                system("PAUSE");
                system("CLS");
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                 ---PENDAFTARAN KARYAWAN---             |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"NAMA           : "<<data_karyawan_sementara.nama<<endl<<endl;
                cout<<"TTL            : "<<data_karyawan_sementara.ttl<<endl<<endl;
                cout<<"JENIS KEL      : "<<data_karyawan_sementara.jenis_kel<<endl<<endl;
                cout<<"ALAMAT         : "<<data_karyawan_sementara.alamat<<endl<<endl;
                cout<<"TELP           : "<<data_karyawan_sementara.no_telp<<endl<<endl;
                if(data_karyawan_sementara.divisi==1)
                    {
                cout<<"DIVISI         : PENDAFTARAN"<<endl;
                    }
                    else if(data_karyawan_sementara.divisi==2)
                    {
                cout<<"DIVISI         : KASIR"<<endl;
                    }
                    else if(data_karyawan_sementara.divisi==3)
                    {
                cout<<"DIVISI         : APOTEKER"<<endl;
                    }
                    cout<<endl;
                cout<<"ID KARYAWAN    : ";
                cin>>data_karyawan_sementara.ID;
                cout<<endl;
                loading();
                system("CLS");
            }
        }
        }while(checking==false);
    }
    if(jml_karyawan==0)
    {
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                 ---PENDAFTARAN KARYAWAN---             |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"                 PENDAFTARAN KARYAWAN BERHASIL\n\n";
        cout<<"         ANDA HARUS MELAKUKAN LOG IN SEBELUM BEKERJA\n\n";
        data_karyawan[sv_ky].ID = data_karyawan_sementara.ID;
        data_karyawan[sv_ky].nama = data_karyawan_sementara.nama;
        data_karyawan[sv_ky].ttl = data_karyawan_sementara.ttl;
        data_karyawan[sv_ky].jenis_kel = data_karyawan_sementara.jenis_kel;
        data_karyawan[sv_ky].alamat = data_karyawan_sementara.alamat;
        data_karyawan[sv_ky].no_telp = data_karyawan_sementara.no_telp;
        data_karyawan[sv_ky].divisi = data_karyawan_sementara.divisi;
    }
    sv_ky++;
    jml_karyawan++;
    system("PAUSE");
    system("CLS");
}
void pendaftaran_obat()
{
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                   ---PENDAFTARAN OBAT---               |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID OBAT        : ";
    cin>>data_obat_sementara.kode_obat;
    cout<<endl;
    cout<<"NAMA OBAT      : ";
    cin.ignore();
    getline(cin, data_obat_sementara.nama_obat);
    cout<<endl;
    cout<<"HARGA OBAT     : ";
    cin>>data_obat_sementara.harga;
    cout<<endl;
    pengecekan_kode_obat();
}
void pengecekan_kode_obat()
{
    loading();
    system("CLS");
    if(jml_obat>0)
    {
        do{
        for(int i=0; i<jml_obat; i++)
        {
            if(data_obat[i].kode_obat==data_obat_sementara.kode_obat)
            {
                checking=false;
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                   ---PENDAFTARAN OBAT---               |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"                   PENDAFTARAN OBAT GAGAL\n\n";
                cout<<"       SILAHKAN MASSUKAN ULANG KODE OBAT YANG BERBEDA\n\n";
                system("PAUSE");
                system("CLS");
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                   ---PENDAFTARAN OBAT---               |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"NAMA OBAT      : "<<data_obat_sementara.nama_obat<<endl<<endl;
                cout<<"HARGA OBAT     : "<<data_obat_sementara.harga<<endl<<endl;
                cout<<"ID OBAT        : ";
                cin>>data_obat_sementara.kode_obat;cout<<endl;
                loading();
                system("CLS");
            }
            else
            {
                checking=true;
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
                cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
                cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"|                   ---PENDAFTARAN OBAT---               |\n";
                cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
                cout<<"                  PENDAFTARAN OBAT BERHASIL\n\n";
                data_obat[sv_ob].kode_obat=data_obat_sementara.kode_obat;
                data_obat[sv_ob].nama_obat=data_obat_sementara.nama_obat;
                data_obat[sv_ob].harga=data_obat_sementara.harga;
            }
        }
    }while(checking==false);
    }
    else if(jml_obat==0)
    {
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"|                   ---PENDAFTARAN OBAT---               |\n";
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        cout<<"                  PENDAFTARAN OBAT BERHASIL\n\n";
        data_obat[sv_ob].kode_obat=data_obat_sementara.kode_obat;
        data_obat[sv_ob].nama_obat=data_obat_sementara.nama_obat;
        data_obat[sv_ob].harga=data_obat_sementara.harga;
    }
            sv_ob++;
        jml_obat++;
    system("PAUSE");
    system("CLS");
}
void edit_data_karyawan()
{
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                  ---EDIT DATA KARYAWAN---               |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID KARYAWAN      : ";
    cin>>data_karyawan_sementara.ID;
    cout<<endl;
    for(int i=0; i<jml_karyawan; i++)
    {
        if(data_karyawan_sementara.ID==data_karyawan[i].ID)
        {
            cout<<"                     ---DATA SEBELUMNYA---\n\n";
            cout<<"NAMA           : "<<data_karyawan[i].nama<<endl<<endl;
            cout<<"TTL            : "<<data_karyawan[i].ttl<<endl<<endl;
            cout<<"JENIS KEL      : "<<data_karyawan[i].jenis_kel<<endl<<endl;
            cout<<"ALAMAT         : "<<data_karyawan[i].alamat<<endl<<endl;
            cout<<"NO TELP        : "<<data_karyawan[i].no_telp<<endl<<endl;
            cout<<"                  ---MASSUKAN PERUBAHAN DATA---\n\n";
            cout<<"ALAMAT         : ";
            getline(cin, data_karyawan[i].alamat);
            cout<<endl;
            cout<<"TTL         : ";
            getline(cin, data_karyawan[i].ttl);
            cout<<endl;
            cout<<"TELP           : ";
            cin.ignore();
            cin>>data_karyawan[i].no_telp;
            cout<<endl;
            cout<<"DIVISI         : 1. PENDAFTARAN\n\n";
            cout<<"                 2. KASIR\n\n";
            cout<<"                 3. APOTEKER\n\n";
            cin>>data_karyawan[i].divisi;
            cout<<endl;
            loading();
            cout<<"                      EDIT DATA BERHASIL!!!\n";
            system("PAUSE");
            system("CLS");
        }
        else
        {
            cout<<"              ID YANG ANDA MASSUKAN BELUM TERDAFTAR\n\n";
            cout<<"                            WARNING!!!\n";
            cout<<"          UNTUK MEMASSUKAN ULANG ID KARYAWAN TEKAN SHIFT\n";
            cout<<"               UNTUK KEMBALI KE MENU UTAMA TEKAN ESC\n\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
            }
            if(GetAsyncKeyState(VK_SHIFT))
            {
                edit_data_karyawan();
            }
            system("PAUSE");
            system("CLS");
        }
    }
}
void edit_data_obat()
{
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                  ---EDIT DATA OBAT---               |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID OBAT        : ";
    cin>>data_obat_sementara.kode_obat;
    for(int i=0; i<jml_obat; i++)
    {
        if(data_obat[i].kode_obat==data_obat_sementara.kode_obat)
        {
            cout<<"                     ---DATA SEBELUMNYA---\n\n";
            cout<<"NAMA OBAT      : "<<data_obat[i].nama_obat<<endl<<endl;
            cout<<"HARGA OBAT     : "<<data_obat[i].harga<<endl<<endl;
            cout<<"                  ---MASSUKAN PERUBAHAN DATA---\n\n";
            cout<<"NAMA OBAT      : ";
            getline(cin, data_obat[i].nama_obat);
            cout<<"HARGA OBAT     : ";
            cin>>data_obat[i].harga;
            loading();
            cout<<"                      EDIT DATA BERHASIL!!!\n";
            system("PAUSE");
            system("CLS");

        }
        else
        {
            cout<<"              ID YANG ANDA MASSUKAN BELUM TERDAFTAR\n\n";
            cout<<"                            WARNING!!!\n";
            cout<<"           UNTUK MEMASSUKAN ULANG ID OBAT TEKAN SHIFT\n";
            cout<<"               UNTUK KEMBALI KE MENU UTAMA TEKAN ESC\n\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
            }
            if(GetAsyncKeyState(VK_SHIFT))
            {
                edit_data_obat();
            }
            system("PAUSE");
            system("CLS");
        }
    }
}
void edit_data_dokter()
{
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                   ---EDIT DATA DOKTER---               |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID DOKTER      : ";
    cin>>data_dokter_sementara.ID;
    cout<<endl;
    for(int i=0; i<jml_dokter; i++)
    {
        if(data_dokter_sementara.ID==data_dokter[i].ID)
        {
            cout<<"                     ---DATA SEBELUMNYA---\n\n";
            cout<<"NAMA           : "<<data_dokter[i].nama<<endl<<endl;
            cout<<"TTL            : "<<data_dokter[i].ttl<<endl<<endl;
            cout<<"JENIS KEL      : "<<data_dokter[i].jenis_kel<<endl<<endl;
            cout<<"ALAMAT         : "<<data_dokter[i].alamat<<endl<<endl;
            cout<<"TELP           : "<<data_dokter[i].no_telp<<endl<<endl;
            cout<<"                  ---MASSUKAN PERUBAHAN DATA---\n\n";
            cout<<"NAMA           : ";
            cout<<data_dokter[i].nama<<endl<<endl;
            getline(cin, data_dokter[i].ttl);
            cout<<endl;
            cout<<"ALAMAT         : ";
            cin.ignore();
            getline(cin, data_dokter[i].alamat);
            cout<<endl;
            cout<<"TELP           : ";
            cin>>data_dokter[i].no_telp;
            cout<<endl;
            cout<<"POLI           : 1. UMUM\n\n";
            cout<<"                 2. GIGI\n\n";
            cout<<"                 3. MATA\n\n";
            cout<<"                 4. ANAK\n\n";
            cout<<"                 5. SYARAF\n\n";
            cout<<"                 6. KANDUNGAN\n\n";
            cout<<"SILAHKAN PILIH POLI UNTUK DOKTER : ";
            cin>>data_dokter[i].poli;
            cout<<endl;
            loading();
            cout<<"                        EDIT DATA BERHASIL!!!\n";
            system("PAUSE");
            system("CLS");
        }
        else
        {
            cout<<"              ID YANG ANDA MASSUKAN BELUM TERDAFTAR\n\n";
            cout<<"                            WARNING!!!\n";
            cout<<"           UNTUK MEMASSUKAN ULANG ID DOKTER TEKAN SHIFT\n";
            cout<<"               UNTUK KEMBALI KE MENU UTAMA TEKAN ESC\n\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
            }
            if(GetAsyncKeyState(VK_SHIFT))
            {
                edit_data_dokter();
            }
            system("PAUSE");
            system("CLS");

        }
    }
}
void edit_data_pasien()
{
        if(jml_obat==0 || jml_pasien==0){
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                     ---PEMERIKSAAN---                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,18);cout<<"MENU PEMERIKSAAN BELUM DAPAT DI AKSES\n\n";
        gotoxy(72,23);system("PAUSE");
        system("CLS");

    }
    string identitas;
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
    cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
    cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"|                   ---EDIT DATA PASIEN---            |\n";
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"No.REKAM MEDIS     : ";
    cin>>identitas;
    cout<<endl;
    for(int i=0; i<jml_pasien; i++)
    {

        if(identitas==data_pasien[i].No_BPJS || identitas==data_pasien[i].NIK)
        {
            cout<<"                     ---DATA SEBELUMNYA---\n\n";
            cout<<"|NAMA           : "<<data_pasien[i].nama;
            cout<<endl;
            cout<<"|UMUR           : "<<data_pasien[i].umur;
            cout<<endl;
            cout<<"|ALAMAT         : "<<data_pasien[i].alamat;
            cout<<endl;
            cout<<"|JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
            cout<<endl;
            cout<<"|GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl;
            cout<<"                  ---MASSUKAN PERUBAHAN DATA---\n\n";
            cout<<"NAMA           : ";
            getline(cin, data_pasien[i].nama);
            cout<<endl;
            cout<<"UMUR           : ";
            cin>>data_pasien[i].umur;
            cout<<endl;
            cout<<"ALAMAT         : ";
            cin.ignore();
            getline(cin, data_pasien[i].alamat);
            cout<<endl;
            cout<<"JENIS KELAMIN  : ";
            getline(cin, data_pasien[i].jenis_kel);
            cout<<endl;
            cout<<"GOLONGAN DARAH : ";
            cin>>data_pasien[i].jenis_kel;
            cout<<endl;
            loading();
            cout<<"EDIT DATA BERHASIL!!!\n";
            system("PAUSE");
            system("CLS");
        }
        else
        {
             cout<<"              ID YANG ANDA MASSUKAN BELUM TERDAFTAR\n\n";
            cout<<"                            WARNING!!!\n";
            cout<<"           UNTUK MEMASSUKAN ULANG ID PASIEN TEKAN SHIFT\n";
            cout<<"               UNTUK KEMBALI KE MENU UTAMA TEKAN ESC\n\n";
            system("PAUSE>NUL");
            if(GetAsyncKeyState(VK_ESCAPE))
            {
                main();
            }
            if(GetAsyncKeyState(VK_SHIFT))
            {
                edit_data_pasien();
            }
            system("PAUSE");
            system("CLS");
        }
    }
}
//DAFTAR DOKTER
void daftar_dokter()
{
    cout<<"     DAFTAR DOKTER HARI INI!!!\n";
    cout<<setw(35)<<setfill('=')<<"\n";
    cout<<"            POLI UMUM\n";
    cout<<setw(35)<<setfill('=')<<"\n";
    if(jml_dokter==0){
    cout<<"     BELUM TERDAPAT DOKTER\n\n";
    }
    for(int i=0;i<jml_dokter;i++){
        if(data_dokter[i].status==true && data_dokter[i].poli==1){
        cout<<"KODE DOKTER      : "<<data_dokter[i].ID<<endl;
        cout<<"NAMA DOKTER      : "<<data_dokter[i].nama<<endl;
        cout<<"NO TELP          : "<<data_dokter[i].no_telp<<endl;
        }
        else{
        cout<<"     BELUM TERDAPAT DOKTER\n\n";
        }
    }
    cout<<setw(35)<<setfill('=')<<"\n";
    cout<<"            POLI GIGI\n";
    cout<<setw(35)<<setfill('=')<<"\n";
        if(jml_dokter==0){
    cout<<"     BELUM TERDAPAT DOKTER\n\n";
    }
    for(int i=0;i<jml_dokter;i++){
        if(data_dokter[i].status==true && data_dokter[i].poli==2){
        cout<<"KODE DOKTER      : "<<data_dokter[i].ID;
        cout<<"NAMA DOKTER      : "<<data_dokter[i].nama;
        cout<<"NO TELP          : "<<data_dokter[i].no_telp<<endl;
        }
        else{
        cout<<"     BELUM TERDAPAT DOKTER\n\n";
        }
    }
    cout<<setw(35)<<setfill('=')<<"\n";
    cout<<"            POLI MATA\n";
    cout<<setw(35)<<setfill('=')<<"\n";
        if(jml_dokter==0){
    cout<<"     BELUM TERDAPAT DOKTER\n\n";
    }
    for(int i=0;i<jml_dokter;i++){
        if(data_dokter[i].status==true && data_dokter[i].poli==3){
        cout<<"KODE DOKTER      : "<<data_dokter[i].ID;
        cout<<"NAMA DOKTER      : "<<data_dokter[i].nama;
        cout<<"NO TELP          : "<<data_dokter[i].no_telp<<endl;
        }
        else{
        cout<<"     BELUM TERDAPAT DOKTER\n\n";
        }
    }
    cout<<setw(35)<<setfill('=')<<"\n";
    cout<<"            POLI ANAK\n";
    cout<<setw(35)<<setfill('=')<<"\n";
        if(jml_dokter==0){
    cout<<"     BELUM TERDAPAT DOKTER\n\n";
    }
    for(int i=0;i<jml_dokter;i++){
        if(data_dokter[i].status==true && data_dokter[i].poli==4){
        cout<<"KODE DOKTER      : "<<data_dokter[i].ID;
        cout<<"NAMA DOKTER      : "<<data_dokter[i].nama;
        cout<<"NO TELP          : "<<data_dokter[i].no_telp<<endl;
        }
        else{
        cout<<"     BELUM TERDAPAT DOKTER\n\n";
        }
    }
    cout<<setw(35)<<setfill('=')<<"\n";
    cout<<"            POLI SYARAF\n";
    cout<<setw(35)<<setfill('=')<<"\n";
        if(jml_dokter==0){
    cout<<"     BELUM TERDAPAT DOKTER\n\n";
    }
    for(int i=0;i<jml_dokter;i++){
        if(data_dokter[i].status==true && data_dokter[i].poli==5){
        cout<<"KODE DOKTER      : "<<data_dokter[i].ID;
        cout<<"NAMA DOKTER      : "<<data_dokter[i].nama;
        cout<<"NO TELP          : "<<data_dokter[i].no_telp<<endl;
        }
        else{
        cout<<"     BELUM TERDAPAT DOKTER\n\n";
        }
    }
    cout<<setw(35)<<setfill('=')<<"\n";
    cout<<"            POLI KANDUNGAN\n";
    cout<<setw(35)<<setfill('=')<<"\n\n";
        if(jml_dokter==0){
    cout<<"     BELUM TERDAPAT DOKTER\n\n";
    }
        for(int i=0;i<jml_dokter;i++){
        if(data_dokter[i].status==true && data_dokter[i].poli==6){
        cout<<"KODE DOKTER      : "<<data_dokter[i].ID;
        cout<<"NAMA DOKTER      : "<<data_dokter[i].nama;
        cout<<"NO TELP          : "<<data_dokter[i].no_telp<<endl;
        }
        else{
        cout<<"     BELUM TERDAPAT DOKTER\n\n";
        }
    }
cout<<setw(35)<<setfill('=')<<"\n\n";
    cout<<"TEKAN esc UNTUK KEMBALI KE MENU UTAMA\n\n";
    system("PAUSE>NUL");
    if(GetAsyncKeyState(VK_ESCAPE))
    {
        system("CLS");
        main();
    }
    else
    {
        system("CLS");
        daftar_dokter();
    }
}
void tampilkan_data(){
        if(jml_obat==0 && jml_pasien==0 && jml_karyawan ==0){
        gotoxy(57,11);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,12);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,13);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,14);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"|                     ---PEMERIKSAAN---                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(68,18);cout<<"MENU PEMERIKSAAN BELUM DAPAT DI AKSES\n\n";
        gotoxy(72,23);system("PAUSE");
        system("CLS");

    }
    else{
                int x=14;
    gotoxy(54,14);
    cout<<"-->";
    bool running =true;
    while(running)
    {
        running=true;
        gotoxy(57,9);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,10);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,11);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,12);
        cout<<"|                        KHUSUS ADMIN                    |\n";
        gotoxy(57,13);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,14);
        cout<<"| TAMPILKAN DATA PASIEN                                  |\n";
        gotoxy(57,15);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,16);
        cout<<"| TAMPILKAN DATA DOKTER                                  |\n";
        gotoxy(57,17);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,18);
        cout<<"| TAMPILKAN DATA KARYAWAN                                |\n";
        gotoxy(57,19);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,20);
        cout<<"| TAMPILKAN DATA OBAT                                    |\n";
        gotoxy(57,21);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        PlaySound(TEXT("pilih_menu.wav"), NULL, SND_SYNC);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_UP))
        {
            gotoxy(54,x);
            cout<<"   ";
            x-=2;
            if(x<14)
            {
                gotoxy(54,14);
                cout<<"-->";
                x=14;
                data_display=1;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                data_display--;
                continue;
            }
        }

        if(GetAsyncKeyState(VK_DOWN))
        {
            gotoxy(54,x);
            cout<<"   ";
            x+=2;
            if(x>20)
            {
                gotoxy(54,20);
                cout<<"-->";
                x=20;
                data_display=4;
            }
            else
            {
                gotoxy(54,x);
                cout<<"-->";
                data_display++;
                continue;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            admin();
        }

        if(GetAsyncKeyState(VK_RETURN))
        {
            switch(data_display)
            {

//PILIHAN MENU UTAMA
            case 1:
            {
                running=false;
                system("CLS");
                tampilkan_data_pasien();
                break;
            }
            case 2:
            {
                running=false;
                system("CLS");
                tampilkan_data_dokter();
                break;
            }
            case 3:
            {
                running=false;
                system("CLS");
                tampilkan_data_karyawan();
                break;
            }
            case 4:
            {
                running=false;
                system("CLS");
                tampilkan_data_obat();
                break;
            }

            }
        }
    }

    }
}
void tampilkan_data_pasien(){
    //DEKLARASI
    int x=74;
    int tampilan_data=1;
    //SOURCE CODE
    system("CLS");
    gotoxy(74,19);
    cout<<"===========";
    gotoxy(74,21);
    cout<<"===========";
    running=true;
    while(running)
    {
        gotoxy(57,10);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,11);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,12);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,13);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,14);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(76,16);
        cout<<"TAMPILAN DATA PASIEN";
        gotoxy(75,20);
        cout<<"SEARCHING";
        gotoxy(90,20);
        cout<<" SORTING";
        gotoxy(68,23);
        cout<<"TEKAN Esc UNTUK KEMBALI KE MENU UTAMA\n\n";
        gotoxy(0,0);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_RIGHT) && x > 73)
        {
            gotoxy(x,19);
            cout<<"           ";
            gotoxy(x,21);
            cout<<"           ";
            x+=15;
            if(x > 73 && x < 90)
            {
                gotoxy(x,19);
                cout<<"===========";
                gotoxy(x,21);
                cout<<"===========";
                tampilan_data++;
                continue;
            }
            if(x > 89)
            {
                gotoxy(89,19);
                cout<<"===========";
                gotoxy(89,21);
                cout<<"===========";
                tampilan_data=2;
                x=89;
            }
        }

        if(GetAsyncKeyState(VK_LEFT) && x < 90)
        {
            gotoxy(x,19);
            cout<<"           ";
            gotoxy(x,21);
            cout<<"           ";
            x-=15;
            if(x<90 && x > 73)
            {
                gotoxy(x,19);
                cout<<"===========";
                gotoxy(x,21);
                cout<<"===========";
                tampilan_data--;
                continue;
            }
            if(x < 73)
            {
                gotoxy(74,19);
                cout<<"===========";
                gotoxy(74,21);
                cout<<"===========";
                tampilan_data=1;
                x=74;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            tampilkan_data();
        }
         if(GetAsyncKeyState(VK_RETURN))
        {
            switch(tampilan_data)
            {
            case 1:
                running=false;
                system("CLS");
                tampilkan_data_pasien_searching();
                break;
            case 2 :
                running=false;
                system("CLS");
                tampilkan_data_pasien_sorting();
                break;
            }
        }
    }
    system("CLS");
}
void tampilkan_data_pasien_searching(){
    //METODHE SEARCHING SEQUENTIAL SEARCH NON SENTINEL
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                    SEARCHING DATA PASIEN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"NO.REKAM MEDIS  : ";
cin>>no_rekam_medis;
cout<<endl;
bool found =false;
int i=0;
loading();
system("CLS");
while((i<jml_pasien)&(!found)){
    if(no_rekam_medis==data_pasien[i].NRM){
            found=true;
        }
        else{
            i+1;
        }

    }
    if(found){
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                         DATA PASIEN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NIK            : "<<data_pasien[i].NIK;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|No.REK MEDIS   : "<<data_pasien[i].NRM;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|NAMA           : "<<data_pasien[i].nama;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|UMUR           : "<<data_pasien[i].umur;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|ALAMAT         : "<<data_pasien[i].alamat;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|JENIS KELAMIN  : "<<data_pasien[i].jenis_kel;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|GOLONGAN DARAH : "<<data_pasien[i].gol_darah;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"|KELUHAN        : "<<data_pasien[i].keluhan;
            cout<<endl;
            cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            if(data_pasien[i].poli==1)
            {
                cout<<"|POLI           : UMUM"<<endl;
            }
            else if(data_pasien[i].poli==2)
            {
                cout<<"|POLI           : GIGI"<<endl;
            }
            else if(data_pasien[i].poli==3)
            {
                cout<<"|POLI           : MATA"<<endl;
            }
            else if(data_pasien[i].poli==4)
            {
                cout<<"|POLI           : ANAK"<<endl;
            }
            else if(data_pasien[i].poli==5)
            {
                cout<<"|POLI           : SYARAF"<<endl;
            }
            else if(data_pasien[i].poli==6)
            {
                cout<<"|POLI           : KANDUNGAN"<<endl;
            }
            cout<<"+"<<setw(59)<<setfill('=')<<"+\n";
                cout<<"| HASIL         : "<<data_pasien[i].data_pemeriksaan[sv_dp].hasil<<endl;
                cout<<"+"<<setw(59)<<setfill('=')<<"+\n\n";
            system("PAUSE");
            system("CLS");
    }
    else{
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                         DATA PASIEN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"             DATA YANG ANDA CARI TIDAK DITEMUKAN\n\n";
cout<<"             TEKAN SPACE UNTUK  MEMASSUKAN ULANG\n";
cout<<"                  TEKAN ESCAPE UNTUK KEMBALI\n";
system("PAUSE>NUL");
if(GetAsyncKeyState(VK_ESCAPE)){
    main();
}
if(GetAsyncKeyState(VK_SPACE)){
    tampilkan_data_pasien_searching();
}
else{
    main();
}

}
}
void tampilkan_data_pasien_sorting(){
    //SORTING DATA PASIEN METODHE BUBBLE SHORT
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                      SORTING DATA PASIEN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
int temp, i, j;
for(int i=0;i<jml_pasien-1;i++){
    for(int j=0;j<jml_pasien-1-i;j++){
        if(data_pasien[j].NRM>data_pasien[j+1].NRM){
            temp=data_pasien[j].NRM;
            data_pasien[j].NRM = data_pasien[j+1].NRM;
            data_pasien[j+1].NRM = temp;
        }
    }
}
for(int i=0;i<jml_pasien;i++){
    cout<<"NRM            : "<<data_pasien[i].NRM<<endl<<endl;
    cout<<"NIK            : "<<data_pasien[i].NIK<<endl<<endl;
    cout<<"NAMA           : "<<data_pasien[i].nama<<endl<<endl;
    cout<<"ALAMAT         : "<<data_pasien[i].alamat<<endl<<endl;
    cout<<"JENIS KELAMIN  : "<<data_pasien[i].jenis_kel<<endl<<endl;
    cout<<"GOLONGAN DARAH : "<<data_pasien[i].gol_darah<<endl<<endl;
    cout<<"KELUHAN        : "<<data_pasien[i].keluhan<<endl<<endl;
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
}
system("PAUSE");
system("CLS");
}
void tampilkan_data_dokter(){
    //DEKLARASI
    int x=74;
    int tampilan_data=1;
    //SOURCE CODE
    system("CLS");
    gotoxy(74,19);
    cout<<"===========";
    gotoxy(74,21);
    cout<<"===========";
    running=true;
    while(running)
    {
        gotoxy(57,10);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,11);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,12);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,13);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,14);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(76,16);
        cout<<"TAMPILAN DATA DOKTER";
        gotoxy(75,20);
        cout<<"SEARCHING";
        gotoxy(90,20);
        cout<<" SORTING";
        gotoxy(68,23);
        cout<<"TEKAN Esc UNTUK KEMBALI KE MENU UTAMA\n\n";
        gotoxy(0,0);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_RIGHT) && x > 73)
        {
            gotoxy(x,19);
            cout<<"           ";
            gotoxy(x,21);
            cout<<"           ";
            x+=15;
            if(x > 73 && x < 90)
            {
                gotoxy(x,19);
                cout<<"===========";
                gotoxy(x,21);
                cout<<"===========";
                tampilan_data++;
                continue;
            }
            if(x > 89)
            {
                gotoxy(89,19);
                cout<<"===========";
                gotoxy(89,21);
                cout<<"===========";
                tampilan_data=2;
                x=89;
            }
        }

        if(GetAsyncKeyState(VK_LEFT) && x < 90)
        {
            gotoxy(x,19);
            cout<<"           ";
            gotoxy(x,21);
            cout<<"           ";
            x-=15;
            if(x<90 && x > 73)
            {
                gotoxy(x,19);
                cout<<"===========";
                gotoxy(x,21);
                cout<<"===========";
                tampilan_data--;
                continue;
            }
            if(x < 73)
            {
                gotoxy(74,19);
                cout<<"===========";
                gotoxy(74,21);
                cout<<"===========";
                tampilan_data=1;
                x=74;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            tampilkan_data();
        }
         if(GetAsyncKeyState(VK_RETURN))
        {
            switch(tampilan_data)
            {
            case 1:
                                running=false;
                system("CLS");
                cout<<"SEARCHING\n\n";
                tampilkan_data_dokter_searching();
                break;
            case 2 :
                                running=false;
                system("CLS");
                cout<<"SORTING\n\n";
                tampilkan_data_dokter_sorting();
                break;
            }
        }
    }
}
void tampilkan_data_dokter_searching(){
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                    SEARCHING DATA DOKTER\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"ID DOKTER     : ";
cin>>data_dokter_sementara.ID;
cout<<endl;
bool found =false;
int i=0;
loading();
system("CLS");
while((i<jml_pasien)&(!found)){
    if(data_dokter[i].ID==data_dokter_sementara.ID){
            found=true;
        }
        else{
            i+1;
        }

    }
    if(found){
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                          DATA DOKTER\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"NAMA           : "<<data_dokter[i].nama<<endl<<endl;
                cout<<"TTL            : "<<data_dokter[i].ttl<<endl<<endl;
                cout<<"JENIS KEL      : "<<data_dokter[i].jenis_kel<<endl<<endl;
                cout<<"ALAMAT         : "<<data_dokter[i].alamat<<endl<<endl;
                cout<<"TELP           : "<<data_dokter[i].no_telp<<endl<<endl;
                    if(data_dokter[i].poli==1)
                    {
                        cout<<"POLI           : UMUM"<<endl;
                    }
                    else if(data_dokter[i].poli==2)
                    {
                        cout<<"POLI           : GIGI"<<endl;
                    }
                    else if(data_dokter[i].poli==3)
                    {
                        cout<<"POLI           : MATA"<<endl;
                    }
                    else if(data_dokter[i].poli==4)
                    {
                        cout<<"POLI           : ANAK"<<endl;
                    }
                    else if(data_dokter[i].poli==5)
                    {
                        cout<<"POLI           : SYARAF"<<endl;
                    }
                    else if(data_dokter[i].poli==6)
                    {
                        cout<<"POLI           : KANDUNGAN"<<endl;
                    }
            system("PAUSE");
            system("CLS");
    }
    else{
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                         DATA PASIEN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"             DATA YANG ANDA CARI TIDAK DITEMUKAN\n\n";
cout<<"             TEKAN SPACE UNTUK  MEMASSUKAN ULANG\n";
cout<<"                  TEKAN ESCAPE UNTUK KEMBALI\n";
system("PAUSE>NUL");
if(GetAsyncKeyState(VK_ESCAPE)){
    main();
}
if(GetAsyncKeyState(VK_SPACE)){
    tampilkan_data_pasien_searching();
}
else{
    main();
}

}
}
void tampilkan_data_dokter_sorting(){
cout<<"HANYA TERSEDIA DI VERSI PREMIUM\n\n";
system("PAUSE");
system("CLS");
}
//KARYAWAN
void tampilkan_data_karyawan()
{
    //DEKLARASI
    int x=74;
    int tampilan_data=1;
    //SOURCE CODE
    system("CLS");
    gotoxy(74,19);
    cout<<"===========";
    gotoxy(74,21);
    cout<<"===========";
    running=true;
    while(running)
    {
        gotoxy(57,10);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(57,11);
        cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
        gotoxy(57,12);
        cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
        gotoxy(57,13);
        cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
        gotoxy(57,14);
        cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
        gotoxy(76,16);
        cout<<"TAMPILAN DATA KARYAWAN";
        gotoxy(75,20);
        cout<<"SEARCHING";
        gotoxy(90,20);
        cout<<" SORTING";
        gotoxy(68,23);
        cout<<"TEKAN Esc UNTUK KEMBALI KE MENU UTAMA\n\n";
        gotoxy(0,0);
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_RIGHT) && x > 73)
        {
            gotoxy(x,19);
            cout<<"           ";
            gotoxy(x,21);
            cout<<"           ";
            x+=15;
            if(x > 73 && x < 90)
            {
                gotoxy(x,19);
                cout<<"===========";
                gotoxy(x,21);
                cout<<"===========";
                tampilan_data++;
                continue;
            }
            if(x > 89)
            {
                gotoxy(89,19);
                cout<<"===========";
                gotoxy(89,21);
                cout<<"===========";
                tampilan_data=2;
                x=89;
            }
        }

        if(GetAsyncKeyState(VK_LEFT) && x < 90)
        {
            gotoxy(x,19);
            cout<<"           ";
            gotoxy(x,21);
            cout<<"           ";
            x-=15;
            if(x<90 && x > 73)
            {
                gotoxy(x,19);
                cout<<"===========";
                gotoxy(x,21);
                cout<<"===========";
                tampilan_data--;
                continue;
            }
            if(x < 73)
            {
                gotoxy(74,19);
                cout<<"===========";
                gotoxy(74,21);
                cout<<"===========";
                tampilan_data=1;
                x=74;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            tampilkan_data();
        }
         if(GetAsyncKeyState(VK_RETURN))
        {
            switch(tampilan_data)
            {
            case 1:
                                running=false;
                system("CLS");
                cout<<"SEARCHING\n\n";
                tampilkan_data_karyawan_searching();
                break;
            case 2 :
                                running=false;
                system("CLS");
                cout<<"SORTING\n\n";
                tampilkan_data_karyawan_sorting();
                break;
            }
        }
    }
}
void tampilkan_data_karyawan_searching(){
 cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                   SEARCHING DATA KARYAWAN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"ID KARYAWAN   : ";
cin>>data_karyawan_sementara.ID;
cout<<endl;
bool found =false;
int i=0;
loading();
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
system("CLS");
while((i<jml_karyawan)&(!found)){
    if(data_karyawan[i].ID==data_karyawan_sementara.ID){
            found=true;
        }
        else{
            i+1;
        }

    }
    if(found){
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                          DATA DOKTER\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
            cout<<"NAMA           : "<<data_dokter[i].nama<<endl<<endl;
            cout<<"TTL            : "<<data_karyawan[i].ttl<<endl<<endl;
            cout<<"JENIS KEL      : "<<data_karyawan[i].jenis_kel<<endl<<endl;
            cout<<"ALAMAT         : "<<data_karyawan[i].alamat<<endl<<endl;
            cout<<"TELP           : "<<data_karyawan[i].no_telp<<endl<<endl;
                    if(data_karyawan[i].divisi==1)
                    {
                        cout<<"DIVISI         : PENDAFTARAN"<<endl;
                    }
                    else if(data_karyawan[i].divisi==2)
                    {
                        cout<<"DIVISI         : KASIR"<<endl;
                    }
                    else if(data_karyawan[i].divisi==3)
                    {
                        cout<<"DIVISI         : APOTEKER"<<endl;
                    }
            system("PAUSE");
            system("CLS");
    }
    else{
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                         DATA PASIEN\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"             DATA YANG ANDA CARI TIDAK DITEMUKAN\n\n";
cout<<"             TEKAN SPACE UNTUK  MEMASSUKAN ULANG\n";
cout<<"                  TEKAN ESCAPE UNTUK KEMBALI\n";
system("PAUSE>NUL");
system("CLS");
if(GetAsyncKeyState(VK_ESCAPE)){
    main();
}
if(GetAsyncKeyState(VK_SPACE)){
    tampilkan_data_pasien_searching();
}
else{
    main();
}

}
}
void tampilkan_data_karyawan_sorting(){
cout<<"HANYA TERSEDIA DI VERSI PREMIUM\n\n";
system("PAUSE");
system("CLS");
}
void tampilkan_data_obat(){
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                      DAFTAR SEMUA OBAT\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
for(int i=0;i<jml_obat;i++){
cout<<"KODE :"<<data_obat[i].kode_obat<<"\t"<<"NAMA :"<<data_obat[i].nama_obat<<"\t\t"<<"HARGA :"<<data_obat[i].harga<<endl;
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
}
cout<<"                  TEKAN ESCAPE UNTUK KEMBALI\n";
cout<<"     TEKAN SPACE UNTUK SORTING DATA OBAT BEDASARKAN HARGA\n\n";
system("PAUSE>NUL");
if(GetAsyncKeyState(VK_ESCAPE)){
        system("CLS");
    admin();
}
if(GetAsyncKeyState(VK_SPACE)){
    system("CLS");
    tampilkan_data_obat_sorting();
}
else{
    system("CLS");
    admin();
}
}
void tampilkan_data_obat_sorting(){
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                      SORTING DATA OBAT\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
int temp, i, j;
for(int i=0;i<jml_obat-1;i++){
    for(int j=0;j<jml_obat-1-i;j++){
        if(data_obat[j].harga>data_obat[j+1].harga){
            temp=data_obat[j].harga;
            data_obat[j].harga = data_obat[j+1].harga;
            data_obat[j+1].harga = temp;
        }
    }
}
for(int i=0;i<jml_obat;i++){
cout<<"KODE :"<<data_obat[i].kode_obat<<"\t"<<"NAMA :"<<data_obat[i].nama_obat<<"\t\t"<<"HARGA :"<<data_obat[i].harga<<endl;
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
}
system("PAUSE>NULL");
if(GetAsyncKeyState(VK_F11)){
   tampilkan_data_obat_sorting();
   }
else{
system("CLS");
}
}
void tampilkan_data_obat_searching(){
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                     SEARCHING DATA OBAT\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"KODE : ";
cin>>data_obat_sementara.kode_obat;
cout<<endl;
loading();
system("CLS");
for(int i=0;i<jml_obat;i++){
        if(data_obat[i].kode_obat==data_obat_sementara.kode_obat){
                    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                   HASIL SEARCHING DATA OBAT\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"KODE         :"<<data_obat[i].kode_obat<<endl<<endl;
cout<<"NAMA         :"<<data_obat[i].nama_obat<<endl<<endl;
cout<<"HARGA        :"<<data_obat[i].harga<<endl;
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
system("PAUSE");
system("CLS");
        }
        else{
cout<<"            DATA YANG ANDA CARI TIDAK DITEMUKAN\n\n";
system("PAUSE");
system("CLS");
        }
}
system("CLS");
}
int hasil(int angka,int pangkat){
    if(pangkat==0){
        return 1;
    }
    else{
        return angka * hasil(angka,pangkat-1);
    }
    }
void login_dokter(){
    int angka,pangkat,input_hasil=0;
    if(jml_dokter==0){
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                        LOGIN DOKTER\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"               BELUM TERDAPAT DOKTER TERDAFTAR\n\n";
cout<<"                 ";system("PAUSE");
    }
    else{
    cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"|          KEMENTRIAN KESEHATAN REPUBLIK INDONESIA       |\n";
cout<<"|               RUMAH SAKIT VETERAN YOGYAKARTA           |\n";
cout<<"|       Jl. Nusa Harapan, Maguwoharjo, Depok, Sleman     |\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
cout<<"                        LOGIN DOKTER\n";
cout<<"+"<<setw(58)<<setfill('=')<<"+\n";
    cout<<"ID DOKTER      : ";
    cin>>data_dokter_sementara.ID;
    cout<<endl;
    cout<<"PASSWORD       : ";
    cin>>data_dokter_sementara.password;
    cout<<endl;
    cout<<"APAKAH ANDA ROBOT?\n\n";
    cout<<"HASIL DARI ";
    for(int i=1;i<=10;i++){
        srand(time(0));
            angka=rand()%10;
    }
    cout<<angka;
        for(int i=1;i<=2;i++){
        srand(time(0));
            pangkat=rand()%2;
    }
    cout<<" PANGKAT ";
    cout<<pangkat<<" ADALAH ";
    cin>>input_hasil;
    cout<<endl<<endl;
    loading();
    cout<<endl<<endl;
    if(input_hasil!=hasil(angka,pangkat)){
    cout<<"                  LOGIN GAGAL";
    cout<<"SYSTEM MENDETEKSI BAHWA ANDA ADALAH ROBOT\n\n";
    system("PAUSE");
}
else{
    for(int i=0;i<jml_dokter;i++){
            if(data_dokter[i].ID == data_dokter_sementara.ID && data_dokter[i].password == data_dokter_sementara.password){
        data_dokter[i].status=true;
        cout<<"                LOGIN BERHASIL\n\n";
        cout<<"  ";
        system("PAUSE");
    }
    else if((data_dokter[i].ID != data_dokter_sementara.ID && data_dokter[i].password != data_dokter_sementara.password) || (data_dokter[i].ID == data_dokter_sementara.ID && data_dokter[i].password != data_dokter_sementara.password)||(data_dokter[i].ID != data_dokter_sementara.ID && data_dokter[i].password == data_dokter_sementara.password)){
        data_dokter[i].status=false;
        cout<<"                  LOGIN GAGAL\n\n";
        cout<<"           TEKAN ESCAPE UNTUK KEMBALI\n";
        cout<<"           TEKAN SPACE UNTUK MEGULANG\n";
        system("PAUSE>NUL");
        system("CLS");
        if(GetAsyncKeyState(VK_SPACE)){
            login_dokter();
        }
        else{
            main();
        }
    }
    }

}
    }
system("CLS");
}
void loading_menu_utama(){
gotoxy(70,23);cout<<"Loading...........";
gotoxy(88,23);cout<<"0%";
Sleep(500);
gotoxy(88,23);cout<<"10%";
Sleep(500);
gotoxy(88,23);cout<<"30%";
Sleep(150);
gotoxy(88,23);cout<<"50%";
Sleep(150);
gotoxy(88,23);cout<<"60%";
Sleep(150);
gotoxy(65,23);cout<<"Checking Data...........";
gotoxy(88,23);cout<<"80%";
Sleep(150);
gotoxy(88,23);cout<<"81%";
Sleep(150);
gotoxy(88,23);cout<<"82%";
Sleep(150);
gotoxy(88,23);cout<<"83%";
Sleep(150);
gotoxy(88,23);cout<<"84%";
Sleep(150);
gotoxy(88,23);cout<<"95%";
Sleep(150);
gotoxy(88,23);cout<<"86%";
Sleep(150);
gotoxy(88,23);cout<<"87%";
Sleep(150);
gotoxy(88,23);cout<<"88%";
Sleep(150);
gotoxy(88,23);cout<<"89%";
Sleep(350);
gotoxy(65,23);cout<<"Verifikasi Data...........";
gotoxy(88,23);cout<<"90%";
Sleep(150);
gotoxy(88,23);cout<<"91%";
Sleep(150);
gotoxy(88,23);cout<<"92%";
Sleep(150);
gotoxy(88,23);cout<<"93%";
Sleep(150);
gotoxy(88,23);cout<<"94%";
Sleep(150);
gotoxy(88,23);cout<<"95%";
Sleep(150);
gotoxy(88,23);cout<<"96%";
Sleep(200);
gotoxy(88,23);cout<<"97%";
Sleep(300);
gotoxy(88,23);cout<<"98%";
Sleep(1000);
gotoxy(88,23);cout<<"99%";
Sleep(1500);
gotoxy(88,23);cout<<"100%";
system("CLS");
}
