//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <string>
#include <fstream>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
using namespace std;
#define SCIEZKA_DO_PLIKU "dane/leki.txt"
//---------------------------------------------------------------------------
vector <string> v_listaLekow;
bool error = false;
AnsiString cTypTitle;
//---------------------------------------------------------------------------
void loadFromFile()
{
        v_listaLekow.clear();
        string line;
        fstream in_file;
        in_file.open(SCIEZKA_DO_PLIKU, ios::in);
        if(in_file)
        {
             while (getline(in_file, line))
             {
                v_listaLekow.push_back(line);
             }
        }
        in_file.close();
}
void saveToFile(string lek)
{
        ofstream in_file;
        in_file.open(SCIEZKA_DO_PLIKU, ios::app);
        if(in_file)
        {
              in_file << "\n" << lek;
        }
        in_file.close();
}
void removeFromFile(int index)
{
        vector <string> v_lekiPlik;

        ifstream in(SCIEZKA_DO_PLIKU);
        string line;
        while(getline(in, line)) v_lekiPlik.push_back(line);
        in.close();

        ofstream out(SCIEZKA_DO_PLIKU);
        for(unsigned int i = 0; i < v_lekiPlik.size(); i++)
        {
                if(i != index) out << v_lekiPlik[i] << endl;
        }
        out.close();
}
void insertDataToListBox()
{
        Form1->ListBox1->Items->Clear();
        for (unsigned int i = 0; i < v_listaLekow.size(); i++)
        {
           Form1->ListBox1->Items->Add(v_listaLekow[i].c_str());
        }
}
string captureDataFromTextBoxes()
{
        string nazwaLeku = Form1->eNazwa->Text.c_str();
        if (nazwaLeku.length() <= 2)
        {
                ShowMessage("Pole nazwa musi zawierac conajmniej 3 znaki");
                error = true;
        }
        string przeznaczenieLeku = Form1->ePrzezn->Text.c_str();
        if (przeznaczenieLeku.length() <= 2)
        {
                ShowMessage("Pole przeznaczenie musi zawierac conajmniej 3 znaki");
                error = true;
        }
        string typLeku = Form1->cTyp->Text.c_str();
        if (cTypTitle.c_str() == typLeku)
        {
                ShowMessage("Pole typu nie zostalo wybrane.");
                error = true;
        }
        string cenaLeku = Form1->eCena->Text.c_str();
        if (cenaLeku.length() == 0)
        {
                ShowMessage("Pole ceny jest puste.");
                error = true;
        }
        else
        {

                for(unsigned int i = 0; i < cenaLeku.length(); i++)
                {
                        if(cenaLeku[i] < '0' || cenaLeku[i] > '9')
                        {
                                ShowMessage("Pole ceny musi zawierac wylacznie cyfry.");
                                error = true;
                                break;
                        }
                }
        }
        return nazwaLeku + "         " + przeznaczenieLeku + "         "+ typLeku + "         " + cenaLeku;
}
void cleanTextBoxes()
{
        Form1->eNazwa->Clear();
        Form1->ePrzezn->Clear();
        Form1->cTyp->Text = cTypTitle;
        Form1->eCena->Clear();
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
        loadFromFile();
        insertDataToListBox();
        cTypTitle = cTyp->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Integer checkedIndex = ListBox1->ItemIndex;
        if(checkedIndex == -1)
        {
                ShowMessage("�aden lek nie zosta� zaznaczony.");
                return;
        }
        removeFromFile(checkedIndex);
        ListBox1->DeleteSelected();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        string lek = captureDataFromTextBoxes();
        if (!error)
        {
                saveToFile(lek);
                loadFromFile();
                insertDataToListBox();
                cleanTextBoxes();
        }
        error = false;
}
//---------------------------------------------------------------------------

