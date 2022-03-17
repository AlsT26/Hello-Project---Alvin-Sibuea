#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define Nil NULL
#define info(P) (P)->info
#define nextEvent(P) (P)->nextEvent
#define prevEvent(P) (P)->prevEvent
#define nextPeserta(P) (P)->nextPeserta
#define prevPeserta(P) (P)->prevPeserta
#define firstEvent(E) ((E).firstEvent)
#define lastEvent(E) ((E).lastEvent)
#define firstPeserta(P) (P)->firstPeserta

#include <iostream>
using namespace std;

typedef struct elmEvent *adrEvent;
typedef struct elmPeserta *adrPeserta;

struct event{
    string nama_event;
    string jenis_event;
    string tanggal;
    string lokasi;
    int kuota;
    int jumlah_daftar;
};
//infotype bertipe event yang berisi data event

struct elmEvent{
    event info;
    adrEvent nextEvent;
    adrEvent prevEvent;
    adrPeserta firstPeserta;
};
//elemen event berisi infotype dan pointer

struct peserta{
    int no_entry;
    string nama;
    string email;
    string telp;
    int seat;
    string jenis_peserta;
};
//infotype peserta berisi data peserta

struct elmPeserta{
    peserta info;
    adrPeserta nextPeserta;
    adrPeserta prevPeserta;
};
//elemen peserta, anak dari multi linked list

struct app{
    adrEvent firstEvent;
    adrEvent lastEvent;
};
//multi linked list nya

void alokasi_app(app &A);
adrEvent new_elmEvent(event event_baru);
adrPeserta new_elmPeserta(peserta peserta_baru);
void insert_last_event(app &A, adrEvent E);
void insert_newEvent(app &A, adrEvent E);
adrEvent search_event(app A, string namaEvent, string jenisEvent);
adrPeserta search_peserta(app &A, string namaEvent, string jenisEvent,string namaPeserta);
void delete_event(app &A, string namaEvent, string jenisEvent);
void insert_first_peserta(app &A, adrPeserta &P, adrEvent &E);
void insert_last_peserta(app &A, adrPeserta &P, adrEvent &E);
void delete_first_peserta(app &A, adrEvent &E, adrPeserta &P);
void delete_peserta(app &A, adrEvent &E, adrPeserta &P);
void pembatalan_daftar(app &A, string namaEvent, string jenisEvent, string namaPeserta, adrPeserta &N);
void insert_peserta(app &A, adrPeserta P, adrEvent &E);
void show_events(app A);
void show_peserta(app A, adrEvent E);
void show_both(app A);
void tampilkan_peserta_event_tertentu(app &A, string namaEvent, string jenisEvent);
void tampilkan_availableEvents(app A);
void show_EventByName(app A, string namaEvent, string jenisEvent, adrEvent &E);
void show_peserta_dalam_event(app A, string namaPeserta, string namaEvent, string jenisEvent, adrEvent &E);
void penambahan_event_baru(app &A, adrEvent &E);
void pendaftaran_peserta_baru(app &A, adrPeserta P);
void pendaftaran_peserta_dengan_alamatEvent(app &A, adrPeserta P, adrEvent &E);
void edit_data_event(app &A, adrEvent &E);

void back_toMenu(int &inputan);
void menu_awal(int &inputan);
void sub_menu(int &subInputan);

#endif // TUBES_H_INCLUDED
