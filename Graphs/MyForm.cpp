#include <Windows.h>
#include "MyForm.h"
#include "Functions.h"

using namespace System;
using namespace System::Windows::Forms;
enum Mode { LongestPath, ShortestPath, NoMode };
Mode currentMode;

[STAThreadAttribute]
int main(array <String^>^ args) {
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Graphs::MyForm form;
    Application::Run(% form);
}

// MyFormLoad

inline Void Graphs::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    this->textBoxN->Hide();
    this->submit_btn1->Hide();
    this->label1->Hide();
    this->label2->Hide();
    this->submit_btn2->Hide();
    this->AdjacencyMatrix->Hide();
    this->IterationsTable->Hide();
    this->label3->Hide();
    this->label4->Hide();
    this->label5->Hide();
    this->GraphsForm->Hide();
    this->SigmaTable->Hide();
    this->DefTable->Hide();
    this->Rat_or_Not->Hide();
    this->AutoScroll = true;
    currentMode = Mode::NoMode;
}

inline Void Graphs::MyForm::textBoxN_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
    if (e->KeyCode == Keys::Enter) {
        e->SuppressKeyPress = true;
        submit_btn1_Click(sender, e);
    }
}

inline Void Graphs::MyForm::submit_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
    if (e->KeyCode == Keys::Enter) {
        e->SuppressKeyPress = true;
        submit_btn2_Click(sender, e);
    }
}

inline Void Graphs::MyForm::textBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
    if (e->KeyChar == (char)Keys::Tab) {
        TextBox^ currentTextBox = dynamic_cast<TextBox^>(sender);
        AdjacencyMatrix->SelectNextControl(currentTextBox, true, true, true, true);
    }
}

inline void Graphs::MyForm::ClearData() {
    this->submit_btn2->Hide();
    this->AdjacencyMatrix->Controls->Clear();
    this->AdjacencyMatrix->Hide();
    this->IterationsTable->Controls->Clear();
    this->IterationsTable->Hide();
    this->SigmaTable->Controls->Clear();
    this->SigmaTable->Hide();
    this->DefTable->Controls->Clear();
    this->DefTable->Hide();
    this->label3->Hide();
    this->label4->Hide();
    this->label5->Hide();
    this->Rat_or_Not->Hide();
    this->GraphsForm->Hide();
    this->label2->Hide();
}

inline void Graphs::MyForm::theLongestPathAndInvestigationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    if (currentMode == Mode::LongestPath) {
        return;
    }
    ClearData();
    currentMode = Mode::LongestPath;
    this->textBoxN->Show();
    this->textBoxN->Focus();
    this->label1->Show();
    this->label1->Text = "Enter the maximum number of tops";
}

inline System::Void Graphs::MyForm::theShortestPathToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    if (currentMode == Mode::ShortestPath) {
        return;
    }
    ClearData();
    currentMode = Mode::ShortestPath;
    this->textBoxN->Show();
    this->textBoxN->Focus();
    this->label1->Show();
    this->label1->Text = "Enter the maximum number of tops";
}

inline Void Graphs::MyForm::submit_btn1_Click(System::Object^ sender, System::EventArgs^ e) {
    ClearData();
    int parsedSize;
    if (!Int32::TryParse(this->textBoxN->Text, parsedSize) || parsedSize <= 0) {
        System::Windows::Forms::MessageBox::Show("Please, enter only numbers higher than 0!", "An error occurred!", MessageBoxButtons::OK);
        return;
    }
    else {
        this->size = parsedSize;
    }
    this->submit_btn2->Show();
    this->submit_btn2->Text = "Submit the adjacency matrix";
    this->AdjacencyMatrix->Show();
    this->AdjacencyMatrix->Controls->Clear();
    this->AdjacencyMatrix->ColumnCount = this->size + 2;
    this->AdjacencyMatrix->RowCount = this->size + 1;
    this->AdjacencyMatrix->ColumnStyles->Clear();
    this->AdjacencyMatrix->RowStyles->Clear();
    this->AdjacencyMatrix->Width = 1300;
    this->AdjacencyMatrix->Height = 750;
    Label^ labelA = gcnew Label();
    labelA->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
    labelA->Text = "A";
    labelA->AutoSize = true;
    labelA->Margin = System::Windows::Forms::Padding(15, 2, 0, 0);
    this->AdjacencyMatrix->SetColumn(labelA, 0);
    this->AdjacencyMatrix->SetRow(labelA, 0);
    this->AdjacencyMatrix->Controls->Add(labelA);
    if (currentMode == Mode::LongestPath) {
        this->label2->Show();
        this->label2->Text = "Enter only 0 or 1 in the cells";
        for (int j = 1; j <= this->size + 1; j++) {
            Label^ labelColumn = gcnew Label();
            labelColumn->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
            labelColumn->Text = (j < this->size + 1) ? System::Convert::ToString(j) : System::Convert::ToString(0);
            labelColumn->AutoSize = true;
            labelColumn->Margin = System::Windows::Forms::Padding(15, 2, 0, 0);
            if (j == this->size + 1) {
                labelColumn->BackColor = System::Drawing::Color::Gray;
            }
            this->AdjacencyMatrix->SetColumn(labelColumn, j);
            this->AdjacencyMatrix->SetRow(labelColumn, 0);
            this->AdjacencyMatrix->Controls->Add(labelColumn);
        }
        for (int i = 1; i <= this->size; i++) {
            Label^ labelRow = gcnew Label();
            labelRow->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
            labelRow->Text = System::Convert::ToString(i);
            labelRow->AutoSize = true;
            labelRow->Margin = System::Windows::Forms::Padding(10, 5, 0, 0);
            this->AdjacencyMatrix->SetColumn(labelRow, 0);
            this->AdjacencyMatrix->SetRow(labelRow, i);
            this->AdjacencyMatrix->Controls->Add(labelRow);
            for (int j = 1; j <= this->size + 1; j++) {
                if (j == i) {
                    Label^ labelDash = gcnew Label();
                    labelDash->Text = "-";
                    labelDash->AutoSize = true;
                    labelDash->Margin = System::Windows::Forms::Padding(15, 5, 1, 1);
                    this->AdjacencyMatrix->Controls->Add(labelDash);
                    this->AdjacencyMatrix->SetColumn(labelDash, j);
                    this->AdjacencyMatrix->SetRow(labelDash, i);
                    continue;
                }
                TextBox^ textBox = gcnew TextBox();
                textBox->Size = System::Drawing::Size(30, 20);
                textBox->Text = "0";
                textBox->BackColor = System::Drawing::Color::LightYellow;
                textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
                textBox->Margin = System::Windows::Forms::Padding(5, 0, 1, 1);
                textBox->TextAlign = HorizontalAlignment::Center;
                textBox->KeyPress += gcnew KeyPressEventHandler(this, &MyForm::textBox_KeyPress);
                if (j == this->size + 1) {
                    textBox->BackColor = System::Drawing::Color::Gray;
                }
                this->AdjacencyMatrix->SetColumn(textBox, j);
                this->AdjacencyMatrix->SetRow(textBox, i);
                this->AdjacencyMatrix->Controls->Add(textBox);
            }
        }
    }
    else if (currentMode == Mode::ShortestPath) {
        this->label2->Show();
        this->label2->Text = "Enter the length of each cell";
        for (int j = 1; j <= this->size; j++) {
            Label^ labelColumn = gcnew Label();
            labelColumn->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
            labelColumn->Text = System::Convert::ToString(j);
            labelColumn->AutoSize = true;
            labelColumn->Margin = System::Windows::Forms::Padding(15, 2, 0, 0);
            this->AdjacencyMatrix->SetColumn(labelColumn, j);
            this->AdjacencyMatrix->SetRow(labelColumn, 0);
            this->AdjacencyMatrix->Controls->Add(labelColumn);
        }
        for (int i = 1; i <= this->size; i++) {
            Label^ labelRow = gcnew Label();
            labelRow->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
            labelRow->Text = System::Convert::ToString(i);
            labelRow->AutoSize = true;
            labelRow->Margin = System::Windows::Forms::Padding(10, 5, 0, 0);
            this->AdjacencyMatrix->SetColumn(labelRow, 0);
            this->AdjacencyMatrix->SetRow(labelRow, i);
            this->AdjacencyMatrix->Controls->Add(labelRow);
            for (int j = 1; j <= this->size; j++) {
                if (j <= i) {
                    Label^ labelDash = gcnew Label();
                    labelDash->Text = "-";
                    labelDash->AutoSize = true;
                    labelDash->Margin = System::Windows::Forms::Padding(15, 5, 1, 1);
                    this->AdjacencyMatrix->Controls->Add(labelDash);
                    this->AdjacencyMatrix->SetColumn(labelDash, j);
                    this->AdjacencyMatrix->SetRow(labelDash, i);
                }
                else {
                    TextBox^ textBox = gcnew TextBox();
                    textBox->Size = System::Drawing::Size(30, 20);
                    textBox->Text = "0";
                    textBox->BackColor = System::Drawing::Color::LightYellow;
                    textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
                    textBox->Margin = System::Windows::Forms::Padding(5, 0, 1, 1);
                    textBox->TextAlign = HorizontalAlignment::Center;
                    textBox->KeyPress += gcnew KeyPressEventHandler(this, &MyForm::textBox_KeyPress);
                    this->AdjacencyMatrix->Controls->Add(textBox);
                    this->AdjacencyMatrix->SetColumn(textBox, j);
                    this->AdjacencyMatrix->SetRow(textBox, i);
                }
            }
        }
    }
    this->IterationsTable->Controls->Clear();
}

inline Void Graphs::MyForm::submit_btn2_Click(System::Object^ sender, System::EventArgs^ e) {
    if(currentMode == Mode::LongestPath){
        if (CheckTableContents1()) {
            const int size1 = this->size;
            int** a = new int* [size1];
            int** b = new int* [size1];
            int** result = new int* [size1];
            int** A = new int* [size1];
            int** new_array = new int* [size1];
            for (int i = 0; i < size1; i++) {
                a[i] = new int[size1]();
                b[i] = new int[size1]();
                result[i] = new int[size1]();
                A[i] = new int[size1 + 1]();
                new_array[i] = new int[1000]();
            }
            this->Rat_or_Not->Hide();
            this->DefTable->Hide();
            this->SigmaTable->Hide();
            this->IterationsTable->Hide();
            int iter_count = 1;
            Matrix1(a, A);
            MultiplyMatrices(a, a, result, size1);
            NewMatrix(0, new_array, a, size1);
            while (!AllZeroes(result, size1)) {
                for (int i = 0; i < size1; i++) {
                    for (int j = 0; j < size1; j++) {
                        b[i][j] = result[i][j];
                    }
                }
                NewMatrix(iter_count, new_array, result, size1);
                MultiplyMatrices(a, b, result, size1);
                iter_count++;
            }
            FindTheDefinitions(A, new_array, iter_count);
            SigmaMatrix(iter_count, a, new_array);
            DrawGraph(A);
            Iterations1(iter_count, new_array);
            this->label3->Text = "Graph's rang is: " + System::Convert::ToString(iter_count);
            this->label3->Location = System::Drawing::Point(15, 120 + size1 * 25);
            this->label3->Show();
            for (int i = 0; i < size1; i++) {
                delete[] a[i];
                delete[] b[i];
                delete[] result[i];
                delete[] A[i];
                delete[] new_array[i];
            }
            delete[] a;
            delete[] b;
            delete[] result;
            delete[] A;
            delete[] new_array;
        }
        else {
            System::Windows::Forms::MessageBox::Show("Please, enter only 0 or 1", "There are numbers not equal to 0 or 1!", MessageBoxButtons::OK);
        }
    }
    else if (currentMode == Mode::ShortestPath) {
        if (CheckTableContents2()) {
            const int size1 = this->size;
            int** a = new int* [size1];
            int** result = new int* [size1];
            for (int i = 0; i < size1; i++) {
                a[i] = new int[size1]();
                result[i] = new int[size1]();

            }
            Matrix2(a);
            Iterations2(a, result);
            for (int i = 0; i < size1; i++) {
                delete[] a[i];
                delete[] result[i];
            }
            delete[] a;
            delete[] result;
        }
        else {
            System::Windows::Forms::MessageBox::Show("Please, enter only 0 or 1", "There are numbers not equal to 0 or 1!", MessageBoxButtons::OK);
        }
    }
}
