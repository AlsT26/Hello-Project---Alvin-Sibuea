#include "tubes.h"
#include <iostream>

using namespace std;

int main()
{
    app A;
    adrEvent E;
    adrPeserta P, N;
    int inputan, subInputan;
    string pilihan;
    inputan = 0;

    alokasi_app(A);

    menu_awal(inputan);

    while (inputan != 0){
        if (inputan == 1){
            show_events(A);
            sub_menu(subInputan);
            if (subInputan == 0){
                menu_awal(inputan);
            }else if (subInputan == 1){
                cout << "+++++++++++" << endl;
                cout << "A. Tampilkan Peserta Untuk Seluruh Event" << endl;
                cout << "B. Tampilkan Peserta Pada Event Tertentu" << endl;
                cout << "+++++++++++" << endl;
                cout << "Pilihan Anda : ";
                cin >> pilihan;
                if (pilihan == "A"){
                    show_both(A);
                    cout << endl;
                    back_toMenu(inputan);
                } else if (pilihan == "B"){
                    string namaEvent, jenisEvent;
                    cout << "Nama Event Yang Ingin Ditampilkan : ";
                    cin >> namaEvent;
                    cout << "Jenis Event : ";
                    cin >> jenisEvent;
                    cout << endl;
                    tampilkan_peserta_event_tertentu(A,namaEvent,jenisEvent);
                    cout << endl;
                    back_toMenu(inputan);
                } else {
                    cout << "Maaf Pilihan Tidak Terdefenisi" << endl;
                    back_toMenu(inputan);
                }
            }else if (subInputan == 2){
                string namaEvent, jenisEvent, namaPeserta;
                cout << "Nama Event : ";
                cin >> namaEvent;
                cout << "Jenis Event : ";
                cin >> jenisEvent;
                cout << "Nama Peserta Yang Dicari : ";
                cin >> namaPeserta;
                cout << endl;
                show_peserta_dalam_event(A, namaPeserta, namaEvent, jenisEvent, E);
                cout << endl;
                if (E == Nil){
                    back_toMenu(inputan);
                } else {
                    cout << "Batalkan Peserta ? (Y/N) : " << endl;
                    cin >> pilihan;
                    if (pilihan == "Y"){
                        cout << "======= Konfirmasi Pembatalan Anda =======" << endl;
                        cout << "Nama Event Peserta Yang Ingin Dibatalkan : ";
                        cin >> namaEvent;
                        cout << "Jenis Event \t\t\t\t : ";
                        cin >> jenisEvent;
                        cout << "Nama Peserta Yang Ingin Dibatalkan \t : ";
                        cin >> namaPeserta;
                        pembatalan_daftar(A, namaEvent, jenisEvent, namaPeserta, N);
                        cout << "Pembatalan Berhasil !!" << endl;
                        back_toMenu(inputan);
                    }
                }
            }else if (subInputan == 3){
                int i;
                cout << "Jumlah Peserta Yang Ingin Ditambahkan : ";
                cin >> i;
                show_events(A);
                cout << endl;
                for (int n=1; n<=i; n++){
                    pendaftaran_peserta_baru(A,P);
                }
                //pendaftaran_peserta_baru(A,P);
                cout << "Pendaftaran Anda Berhasil" << endl;
                cout << endl;
                back_toMenu(inputan);
            }else if (subInputan == 4){
                tampilkan_availableEvents(A);
                cout << endl << "Daftarkan Peserta Pada Event Yang Masih Available ? (Y/N) : ";
                cin >> pilihan;
                if (pilihan == "Y"){
                    int i;
                    cout << "Jumlah Peserta Yang Ingin Ditambahkan : ";
                    cin >> i;
                    //tampilkan_availableEvents(A);
                    for (int n=1; n<=i; n++){
                        pendaftaran_peserta_baru(A,P);
                    }
                    //pendaftaran_peserta_baru(A,P);
                    cout << "Pendaftaran Anda Berhasil" << endl;
                    cout << endl;
                    back_toMenu(inputan);
                }else {
                    back_toMenu(inputan);
                }
            }else {
                subInputan = 0;
            }
        }else if (inputan == 2){
            int i;
            cout << "Jumlah Event Yang Ingin Ditambah : ";
            cin >> i;
            cout << endl;
            for (int n=1; n<=i; n++){
                penambahan_event_baru(A, E);
            }
            cout << "Event Baru Berhasil Ditambahkan !!" << endl;
            cout << endl;
            back_toMenu(inputan);
        }else if (inputan == 3){
            string namaEvent, jenisEvent;
            cout << "Nama Event Yang Ingin Ditampilkan : ";
            cin >> namaEvent;
            cout << "Jenis Event Yang Dicari : ";
            cin >> jenisEvent;
            cout << endl;
            show_EventByName(A, namaEvent, jenisEvent, E);
            cout << "----------------------------------" << endl;
            cout << "A. Tambahkan Peserta Ke Event Ini" << endl;
            cout << "B. Ubah Data Event Ini" << endl;
            cout << "C. Kembali Ke Menu Utama" << endl;
            cout << "----------------------------------" << endl;
            cout << "Pilihan Anda : ";
            cin >> pilihan;
            if (pilihan == "C"){
                back_toMenu(inputan);
            }else if (pilihan == "A"){
                int i;
                cout << endl << "Jumlah Peserta Yang Ingin Ditambahkan : ";
                cin >> i;
                for (int n=1; n<=i; n++){
                    pendaftaran_peserta_dengan_alamatEvent(A, P, E);
                }
                cout << endl << "Peserta Baru Berhasil Ditambahkan";
                cout << endl << "---------------------------------" << endl;
                back_toMenu(inputan);
            }else if (pilihan == "B"){
                edit_data_event(A,E);
                cout << endl << endl;
                back_toMenu(inputan);
            }
        }else {
            inputan = 0;
        }
    }
    cout << "Sampai Jumpa !!" << endl;

    return 0;
}
