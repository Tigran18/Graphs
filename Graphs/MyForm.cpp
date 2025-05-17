#include <Windows.h>
#include "MyForm.h"
#include "Functions.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.IO.dll>

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Threading;

enum Mode { LongestPath, ShortestPath, NoMode };
Mode currentMode;

[STAThreadAttribute]

int main(array<String^>^ args) {
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Graphs::MyForm form;
    Application::Run(% form);
}

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
		textBoxN->Text = "";
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
    this->SuspendLayout();
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
    this->ResumeLayout();
}

inline void Graphs::MyForm::theLongestPathAndInvestigationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    if (currentMode == Mode::LongestPath) {
        return;
    }
    ClearData();
    currentMode = Mode::LongestPath;
    this->textBoxN->Show();
    this->submit_btn1->Show();
    this->submit_btn1->Text = "Browse File or Enter Size";
    this->textBoxN->Focus();
    this->label1->Show();
    this->label1->Text = "Enter number of vertices or click Browse to select file";
}

inline System::Void Graphs::MyForm::theShortestPathToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
    if (currentMode == Mode::ShortestPath) {
        return;
    }
    ClearData();
    currentMode = Mode::ShortestPath;
    this->textBoxN->Show();
    this->submit_btn1->Show();
    this->submit_btn1->Text = "Submit Size";
    this->textBoxN->Focus();
    this->label1->Show();
    this->label1->Text = "Enter the maximum number of vertices";
}

inline Void Graphs::MyForm::submit_btn1_Click(System::Object^ sender, System::EventArgs^ e) {
    ClearData();
    int parsedSize;

    if (currentMode == Mode::LongestPath) {
        // Check if textBoxN contains a valid number
        if (Int32::TryParse(this->textBoxN->Text, parsedSize) && parsedSize > 0) {
            // Numeric input: proceed directly to matrix setup
            this->size = parsedSize;
        }
        else {
            // Non-numeric or invalid input: show file dialog
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
            openFileDialog->Title = "Select Graph Edge List File";
            openFileDialog->InitialDirectory = System::IO::Directory::GetCurrentDirectory();

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                this->textBoxN->Text = openFileDialog->FileName;
                try {
                    StreamReader^ reader = gcnew StreamReader(openFileDialog->FileName);
                    System::String^ edgeCountLine = reader->ReadLine();
                    int edgeCount;
                    if (!Int32::TryParse(edgeCountLine, edgeCount) || edgeCount < 0) {
                        reader->Close();
                        MessageBox::Show("Invalid number of edges! First line must be a non-negative integer.", "Error", MessageBoxButtons::OK);
                        return;
                    }
                    int maxVertex = 0;
                    array<int>^ fromVertices = gcnew array<int>(edgeCount);
                    array<int>^ toVertices = gcnew array<int>(edgeCount);
                    for (int i = 0; i < edgeCount; i++) {
                        System::String^ line = reader->ReadLine();
                        if (String::IsNullOrEmpty(line)) {
                            reader->Close();
                            MessageBox::Show("Incomplete edge list! Fewer edges than specified.", "Error", MessageBoxButtons::OK);
                            return;
                        }
                        array<String^>^ values = line->Split(' ');
                        if (values->Length != 2) {
                            reader->Close();
                            MessageBox::Show("Invalid edge format! Each line must have two integers.", "Error", MessageBoxButtons::OK);
                            return;
                        }
                        int from, to;
                        if (!Int32::TryParse(values[0], from) || !Int32::TryParse(values[1], to)) {
                            reader->Close();
                            MessageBox::Show("Invalid vertex indices! Edges must be integers.", "Error", MessageBoxButtons::OK);
                            return;
                        }
                        if (from < 0 || to < 0) {
                            reader->Close();
                            MessageBox::Show("Vertex indices must be non-negative!", "Error", MessageBoxButtons::OK);
                            return;
                        }
                        fromVertices[i] = from;
                        toVertices[i] = to;
                        maxVertex = Math::Max(maxVertex, Math::Max(from, to));
                    }
                    reader->Close();
                    parsedSize = maxVertex;
                    if (parsedSize <= 0) {
                        MessageBox::Show("No valid vertices found in edge list!", "Error", MessageBoxButtons::OK);
                        return;
                    }
                    this->size = parsedSize;
                    array<int, 2>^ matrix = gcnew array<int, 2>(parsedSize, parsedSize + 1);
                    for (int i = 0; i < parsedSize; i++) {
                        for (int j = 0; j <= parsedSize; j++) {
                            matrix[i, j] = 0;
                        }
                    }
                    for (int i = 0; i < edgeCount; i++) {
                        int from = fromVertices[i];
                        int to = toVertices[i];
                        if (from > 0 && to > 0 && from <= parsedSize && to <= parsedSize) {
                            matrix[from - 1, to - 1] = 1;
                        }
                        else if (from > 0 && to == 0 && from <= parsedSize) {
                            matrix[from - 1, parsedSize] = 1;
                        }
                    }
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
                    this->label2->Show();
                    this->label2->Text = "Adjacency matrix loaded from file. Click Submit to analyze.";
                    for (int j = 1; j <= this->size + 1; j++) {
                        Label^ labelColumn = gcnew Label();
                        labelColumn->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
                        labelColumn->Text = (j < this->size + 1) ? System::Convert::ToString(j) : "0";
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
                            if (j == i && j <= this->size) {
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
                            textBox->Text = System::Convert::ToString(matrix[i - 1, j - 1]);
                            textBox->BackColor = System::Drawing::Color::LightYellow;
                            textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10);
                            textBox->Margin = System::Windows::Forms::Padding(5, 0, 1, 1);
                            textBox->TextAlign = HorizontalAlignment::Center;
                            textBox->ReadOnly = true;
                            if (j == this->size + 1) {
                                textBox->BackColor = System::Drawing::Color::Gray;
                            }
                            this->AdjacencyMatrix->SetColumn(textBox, j);
                            this->AdjacencyMatrix->SetRow(textBox, i);
                            this->AdjacencyMatrix->Controls->Add(textBox);
                        }
                    }
                    this->AdjacencyMatrix->Refresh();
                    this->Update();
                    this->submit_btn2->Show();
                    this->submit_btn2->Text = "Analyze Graph";
                    return;
                }
                catch (System::IO::FileNotFoundException^) {
                    MessageBox::Show("File not found!", "Error", MessageBoxButtons::OK);
                    return;
                }
                catch (System::Exception^ ex) {
                    MessageBox::Show("Error reading file: " + ex->Message, "Error", MessageBoxButtons::OK);
                    return;
                }
            }
            // User canceled file dialog and no valid number entered
            MessageBox::Show("Please enter a number greater than 0 or select a file!", "Error", MessageBoxButtons::OK);
            return;
        }
    }
    else if (currentMode == Mode::ShortestPath) {
        if (!Int32::TryParse(this->textBoxN->Text, parsedSize) || parsedSize <= 0) {
            MessageBox::Show("Please enter a number greater than 0!", "Error", MessageBoxButtons::OK);
            return;
        }
    }
    else {
        MessageBox::Show("Invalid mode!", "Error", MessageBoxButtons::OK);
        return;
    }

    // Numeric input matrix setup (for both LongestPath and ShortestPath)
    this->size = parsedSize;
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
            labelColumn->Text = (j < this->size + 1) ? System::Convert::ToString(j) : "0";
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
    this->AdjacencyMatrix->Refresh();
    this->Update();
    this->IterationsTable->Controls->Clear();
}

inline Void Graphs::MyForm::submit_btn2_Click(System::Object^ sender, System::EventArgs^ e) {
    if (currentMode == Mode::LongestPath) {
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
            this->label2->Text = "Analysis complete. Results displayed below.";
            this->AdjacencyMatrix->Refresh();
            this->Update();
        }
        else {
            MessageBox::Show("Please, enter only 0 or 1", "There are numbers not equal to 0 or 1!", MessageBoxButtons::OK);
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
            this->label2->Text = "Shortest path analysis complete.";
            this->AdjacencyMatrix->Refresh();
            this->Update();
        }
        else {
            MessageBox::Show("Please, enter only 0 or 1", "There are numbers not equal to 0 or 1!", MessageBoxButtons::OK);
        }
    }
}