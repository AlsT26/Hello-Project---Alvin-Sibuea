#include "tubes.h"

void alokasi_app(app &A){
    firstEvent(A) = Nil;
    lastEvent(A) = Nil;
}
//membuat mll baru / alokasi mll baru

adrEvent new_elmEvent(event event_baru){
    adrEvent P = new elmEvent;
    info(P) = event_baru;
    nextEvent(P) = Nil;
    prevEvent(P) = Nil;
    firstPeserta(P) = Nil;

    return P;
}
//membuat elemen event baru

adrPeserta new_elmPeserta(peserta peserta_baru){
    adrPeserta P = new elmPeserta;
    info(P) = peserta_baru;
    nextPeserta(P) = Nil;
    prevPeserta(P) = Nil;

    return P;
}

void insert_last_event(app &A, adrEvent E){
    adrEvent P = lastEvent(A);
    nextEvent(P) = E;
    prevEvent(E) = P;
    lastEvent(A) = E;
}
//memasukkan event baru di bagian terakhir list

void insert_newEvent(app &A, adrEvent E){
    if (firstEvent(A) == Nil){
        firstEvent(A) = E;
        lastEvent(A) = E;
    }else{
        insert_last_event(A, E);
    }
}
//proses memasukkan event baru ke list

adrEvent search_event(app A, string namaEvent, string jenisEvent){
    adrEvent P = firstEvent(A);
    if (P == Nil){
        return Nil;
    }else {
        while (P != Nil){
            if ((info(P).nama_event == namaEvent) && (info(P).jenis_event == jenisEvent)){
                return P;
            }else{
                P = nextEvent(P);
            }
        }
        return Nil;
    }
}
//mereturn alamat event yang dicari

adrPeserta search_peserta(app &A, string namaEvent, string jenisEvent,string namaPeserta){
    adrEvent P = search_event(A, namaEvent, jenisEvent);
    if (P == Nil){
        return Nil;
    } else{
        adrPeserta X = firstPeserta(P);
        while (X != Nil){
            if (info(X).nama == namaPeserta){
                return X;
            }else {
                X = nextPeserta(X);
            }
        }
        return Nil;
    }
}
//mereturn alamat peserta yang dicari, NUll jika tidak ketemu

void delete_event(app &A, string namaEvent, string jenisEvent){
    if (search_event(A, namaEvent, jenisEvent) == Nil){
        cout << "Maaf event tersebut tidak ada di kegiatan kali ini." << endl;
    }else {
        adrEvent P = search_event(A, namaEvent, jenisEvent);
        if (firstEvent(A) == P && lastEvent(A) == P){
            firstEvent(A) = Nil;
            lastEvent(A) = Nil;
        }else if (firstEvent(A) == P){
            adrEvent Q = nextEvent(P);
            firstEvent(A) = Q;
            prevEvent(Q) = Nil;
            nextEvent(P) = Nil;
        }else if (lastEvent(A) == P){
            adrEvent Q = prevEvent(P);
            lastEvent(A) = Q;
            nextEvent(Q) = Nil;
            prevEvent(P) = Nil;
        }else {
            adrEvent Q = prevEvent(P);
            nextEvent(Q) = nextEvent(P);
            prevEvent(nextEvent(P)) = Q;
            prevEvent(P) = Nil;
            nextEvent(P) = Nil;
        }
        cout << "Event telah dihapus." << endl;
    }
}
//menghapus sebuah event dalam list event

void insert_first_peserta(app &A, adrPeserta &P, adrEvent &E){
    firstPeserta(E) = P;
    prevPeserta(P) = Nil;
    nextPeserta(P) = Nil;
}

void insert_last_peserta(app &A, adrPeserta &P, adrEvent &E){
    adrPeserta X = firstPeserta(E);
    while (nextPeserta(X) != Nil){
        X = nextPeserta(X);
    }
    nextPeserta(X) = P;
    prevPeserta(P) = X;
}

void delete_first_peserta(app &A, adrEvent &E, adrPeserta &P){
    if (nextPeserta(firstPeserta(E)) == Nil){
        firstPeserta(E) = Nil;
    }else{
        P = firstPeserta(E);
        adrPeserta Q = nextPeserta(P);
        firstPeserta(E) = Q;
        prevPeserta(Q) = Nil;
        nextPeserta(P) = Nil;
    }
}
//menghapus data elemen peserta di awal list

void delete_peserta(app &A, adrEvent &E, adrPeserta &P){
    adrPeserta X = prevPeserta(P);
    if (nextPeserta(P) == Nil){
        nextPeserta(X) = Nil;
        prevPeserta(P) = Nil;
    } else{
        nextPeserta(X) = nextPeserta(P);
        prevPeserta(nextPeserta(X)) = X;
        nextPeserta(P) = Nil;
        prevPeserta(P) = Nil;
    }
}
//proses penghapusan elemen peserta

void pembatalan_daftar(app &A, string namaEvent, string jenisEvent, string namaPeserta, adrPeserta &N){
    adrEvent P = search_event(A,namaEvent,jenisEvent);
    if (P == Nil){
        cout << "Event tidak ada" << endl;
    }else{
        adrPeserta Q = search_peserta(A,namaEvent,jenisEvent,namaPeserta);
        if (Q == Nil){
            cout << "Nama anda tidak terdaftar"<< endl;
        } else {
            if (firstPeserta(P) == Q){
                delete_first_peserta(A,P,Q);
            } else {
                delete_peserta(A,P,Q);
            }
        }
        N = firstPeserta(P);
        while (info(N).jenis_peserta == "REGULER"){
            N = nextPeserta(N);
        }
        info(N).jenis_peserta = "REGULER";

        info(P).jumlah_daftar--;
    }
}

void insert_peserta(app &A, adrPeserta P, adrEvent &E){
    info(E).jumlah_daftar++;
    if (firstPeserta(E) == Nil){
        insert_first_peserta(A, P, E);
        //info(E).jumlah_daftar++;
        info(P).jenis_peserta = "REGULER";
    }else{
        if (info(E).jumlah_daftar > info(E).kuota){
            insert_last_peserta(A,P,E);
            //info(E).jumlah_daftar++;
            info(P).jenis_peserta = "WAITING LIST";
        }else{
            insert_last_peserta(A,P,E);
            //info(E).jumlah_daftar++;
            info(P).jenis_peserta = "REGULER";
        }
    }
    //cout << info(E).jumlah_daftar;
}

void show_events(app A){
    adrEvent P = firstEvent(A);
    if (P == Nil){
        cout << "Tidak Ada Event Untuk Diikuti" << endl;
    } else{
        while (nextEvent(P) != Nil){
            cout << "Nama Event\t\t: " << info(P).nama_event << endl;
            cout << "Jenis Event\t\t: " << info(P).jenis_event << endl;
            cout << "Tanggal Pelaksanaan\t: " << info(P).tanggal << endl;
            cout << "Tempat Pelaksanaan \t: " << info(P).lokasi << endl;
            cout << "Kuota Maks\t\t: " << info(P).kuota << endl;
            cout << "Jumlah Pendaftar\t: " << info(P).jumlah_daftar << endl;
            cout << endl;
            P = nextEvent(P);
        }
        cout << "Nama Event\t\t : " << info(P).nama_event << endl;
        cout << "Jenis Event\t\t : " << info(P).jenis_event << endl;
        cout << "Tanggal Pelaksanaan\t : " << info(P).tanggal << endl;
        cout << "Tempat Pelaksanaan\t : " << info(P).lokasi << endl;
        cout << "Kuota Maks\t\t : " << info(P).kuota << endl;
        cout << "Jumlah Pendaftar\t : " << info(P).jumlah_daftar << endl;
    }
}

void show_peserta(app A, adrEvent E){
    adrPeserta P = firstPeserta(E);
    if (P == Nil){
        cout << "Tidak Ada Peserta Yang Mengikuti Event Ini" << endl;
    } else {
        while (nextPeserta(P) != Nil){
            cout << "No. Peserta \t : " << info(P).no_entry << endl;
            cout << "Nama Peserta \t : " << info(P).nama << endl;
            cout << "Email \t\t : " << info(P).email << endl;
            cout << "No. Telepon \t : " << info(P).telp << endl;
            cout << "No. Tempat Duduk : " << info(P).seat << endl;
            cout << "Jenis Peserta \t : " << info(P).jenis_peserta << endl;
            cout << endl;
            P = nextPeserta(P);
        }
        cout << "No. Peserta \t : " << info(P).no_entry << endl;
        cout << "Nama Peserta \t : " << info(P).nama << endl;
        cout << "Email \t\t : " << info(P).email << endl;
        cout << "No. Telepon \t : " << info(P).telp << endl;
        cout << "No. Tempat Duduk : " << info(P).seat << endl;
        cout << "Jenis Peserta \t : " << info(P).jenis_peserta << endl;
        cout << endl;
    }
}

void show_both(app A){
    adrEvent E = firstEvent(A);
    //adrPeserta P = firstPeserta(E);
    if (E == Nil){
        cout << "Tidak Ada Event Saat Ini" << endl;
    } else {
        while (E != Nil){
            cout << "Nama Event : " << info(E).nama_event << endl;
            cout << endl;
            show_peserta(A,E);
            E = nextEvent(E);
        }
        cout << "============================" << endl;
    }
}

void tampilkan_peserta_event_tertentu(app &A, string namaEvent, string jenisEvent){
    adrEvent E = search_event(A, namaEvent, jenisEvent);
    if (E == Nil){
        cout << "Event Yang Anda Maksud Tidak Ada" << endl;
    } else{
        cout << "Nama Event : " << info(E).nama_event << endl;
        cout << endl;
        show_peserta(A,E);
    }
}

void tampilkan_availableEvents(app A){
    adrEvent E = firstEvent(A);
    int jum = 0;
    if (E == Nil){
        cout << "Tidak Ada Event Yang Dapat Diikuti" << endl;
    } else {
        while(E != Nil){
            if (info(E).kuota > info(E).jumlah_daftar){
                jum++;
                E = nextEvent(E);
            } else {
                E = nextEvent(E);
            }
        }
        if (jum == 0){
            cout << "Tidak Ada Event Yang Dapat Diikuti" << endl;
        } else {
            cout << "Ada " << jum << " Event Yang Masih Available, Yaitu:" << endl;
            cout << endl;
            E = firstEvent(A);
            while(E != Nil){
            if (info(E).kuota > info(E).jumlah_daftar){
                cout << "Nama Event \t\t : " << info(E).nama_event << endl;
                cout << "Jenis Event \t\t : " << info(E).jenis_event << endl;
                cout << "Tanggal Pelaksanaan \t : " << info(E).tanggal << endl;
                cout << "Tempat Pelaksanaan \t : " << info(E).lokasi << endl;
                cout << "Kuota Maks \t\t : " << info(E).kuota << endl;
                cout << "Jumlah Pendaftar \t : " << info(E).jumlah_daftar << endl;
                cout << endl;
                E = nextEvent(E);
            } else {
                E = nextEvent(E);
            }
            }
        }
    }
}

void show_EventByName(app A, string namaEvent, string jenisEvent, adrEvent &E){
    E = search_event(A, namaEvent, jenisEvent);
    if (E == Nil){
        cout << "Event Tidak Tersedia" << endl;
    } else {
        cout << "Nama Event \t\t : " << info(E).nama_event << endl;
        cout << "Jenis Event \t\t : " << info(E).jenis_event << endl;
        cout << "Tanggal Pelaksanaan \t : " << info(E).tanggal << endl;
        cout << "Tempat Pelaksanaan \t : " << info(E).lokasi << endl;
        cout << "Kuota Maks \t\t : " << info(E).kuota << endl;
        cout << "Jumlah Pendaftar \t : " << info(E).jumlah_daftar << endl;
    }
}

void show_peserta_dalam_event(app A, string namaPeserta, string namaEvent, string jenisEvent, adrEvent &E){
    E = search_event(A, namaEvent, jenisEvent);
    if (E == Nil){
        cout << "Event Tidak Tersedia" << endl;
    } else {
        adrPeserta P = search_peserta(A, namaEvent, jenisEvent, namaPeserta);
        if (P == Nil){
            cout << "Peserta Tidak Ada di Event Ini" << endl;
        } else {
            cout << "Event Yang Diikuti : " << info(E).nama_event << endl;
            cout << "No. Peserta \t\t : " << info(P).no_entry << endl;
            cout << "Nama Peserta \t\t : " << info(P).nama << endl;
            cout << "Email \t\t\t : " << info(P).email << endl;
            cout << "No. Telepon \t\t : " << info(P).telp << endl;
            cout << "No. Tempat Duduk \t : " << info(P).seat << endl;
            cout << "Jenis Peserta \t\t : " << info(P).jenis_peserta << endl;
            cout << endl;
        }
    }
}

void penambahan_event_baru(app &A, adrEvent &E){
    event kegiatan;
    cout << "Nama Kegiatan Yang Ingin Ditambah : ";
    cin >> kegiatan.nama_event;
    cout << "Jenis Event Baru \t\t  : ";
    cin >> kegiatan.jenis_event;
    cout << "Tanggal Dilaksanakannya \t : ";
    cin >> kegiatan.tanggal;
    cout << "Lokasi Event \t\t\t : ";
    cin >> kegiatan.lokasi;
    cout << "Kuota Peserta Maks \t\t  : ";
    cin >> kegiatan.kuota;
    cout << endl;
    kegiatan.jumlah_daftar = 0;

    E = new_elmEvent(kegiatan);
    insert_newEvent(A, E);

    //cout << "Event Baru Berhasil Ditambahkan !!" << endl;
}

void pendaftaran_peserta_baru(app &A, adrPeserta P){
    string namaEvent, jenisEvent;
    peserta entry;
    cout << "Nama Event Yang Ingin Anda Ikuti : ";
    cin >> namaEvent;
    cout << "Jenis Event \t\t\t : ";
    cin >> jenisEvent;

    adrEvent E = search_event(A, namaEvent, jenisEvent);
    int i;
    if (E == Nil){
        cout << "Event Tidak Tersedia" << endl;
        back_toMenu(i);
    } else {
        cout << endl;
        cout << "Nama Anda \t : ";
        cin >> entry.nama;
        cout << "Email Anda \t: ";
        cin >> entry.email;
        cout << "No. Telepon Anda : ";
        cin >> entry.telp;
        entry.no_entry = rand();
        entry.seat = rand();

        P = new_elmPeserta(entry);
        insert_peserta(A,P,E);

        cout << endl;

        //cout << "Pendaftaran Anda Berhasil" << endl;
    }
}

void pendaftaran_peserta_dengan_alamatEvent(app &A, adrPeserta P, adrEvent &E){
    peserta entry;
    if (E == Nil){
        cout << "Event Tidak Tersedia" << endl;
    } else {
        cout << "Nama Anda : ";
        cin >> entry.nama;
        cout << "Email Anda : ";
        cin >> entry.email;
        cout << "No. Telepon Anda : ";
        cin >> entry.telp;
        entry.no_entry = rand();
        entry.seat = rand();

        P = new_elmPeserta(entry);
        insert_peserta(A,P,E);

        //cout << "Pendaftaran Anda Berhasil" << endl;
    }
}

void edit_data_event(app &A, adrEvent &E){
    string opt, ganti;
    int x;
    cout << "------------------------" << endl;
    cout << "A. Ganti Nama Event" << endl;
    cout << "B. Ganti Tanggal Event" << endl;
    cout << "C. Ganti Lokasi Event" << endl;
    cout << "D. Ubah Kuota Maks" << endl;
    cout << "Z. Menu Utama" << endl;
    cout << "------------------------" << endl;
    cout << "Pilihan Anda : ";
    cin >> opt;
    cout << endl;
    if (opt == "A"){
        cout << "Masukkan Nama Event Yang Baru : ";
        cin >> ganti;
        info(E).nama_event = ganti;
        cout << "Nama Event Berhasil Diganti" << endl;
    } else if (opt == "B"){
        cout << "Masukkan Tanggal Event Yang Baru : ";
        cin >> ganti;
        info(E).tanggal = ganti;
        cout << "Tanggal Event Berhasil Diperbarui" << endl;
    } else if (opt == "C"){
        cout << "Masukkan Lokasi Baru : ";
        cin >> ganti;
        info(E).lokasi = ganti;
        cout << "Lokasi Event Berhasil Diperbarui" << endl;
    } else if (opt == "D"){
        cout << "Masukkan Kuota Event Yang Baru : " << endl;
        cin >> x;
        info(E).kuota = x;
        cout << "Kuota Event Berhasil Diperbarui" << endl;
    } else {
        cout << endl;
    }
}

void back_toMenu(int &inputan){
    string inputan_YesNo;
    cout << "Kembali Ke Menu Utama ? (Y/N) : ";
    cin >> inputan_YesNo;
    cout << endl;
    if (inputan_YesNo == "Y"){
        menu_awal(inputan);
    }else {
        inputan = 0;
    }
}

void menu_awal(int &inputan){
    inputan = 0;
    system("cls");
    cout << "====================== MENU ========================" << endl;
    cout << "1. Tampilkan Semua Event" << endl;
    cout << "2. Tambah Event" << endl;
    cout << "3. Cari Event" << endl;
    cout << "0. Exit" << endl;
    cout << "====================================================" << endl;
    cout << "Masukkan Menu Pilihan Anda : ";
    cin >> inputan;
    cout << endl;
}

void sub_menu(int &subInputan){
    //system("cls");
    //int inputan;
    //string pilihan;
    cout << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. Tampilkan Peserta Dalam Event" << endl;
    //setelah tampilkan peserta bisa dipilih untuk 1 event atau semua event
    cout << "2. Cari Peserta" << endl;
    //tanya apakah mau dibatalkan peserta itu atau gak
    cout << "3. Daftarkan Peserta" << endl;
    cout << "4. Tampilkan Event Yang Available" << endl;
    //tanya user mau gak daftarkan ke event yang available itu ?
    cout << "0. Kembali Ke Menu Utama" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Masukkan Pilihan Anda : ";
    cin >> subInputan;
    cout << endl;
}
