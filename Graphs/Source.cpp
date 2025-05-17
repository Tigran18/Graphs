#include "MyForm.h"
#include <math.h>
#include "Functions.h"

using namespace Graphs;

//The longest path and investigation

inline void MyForm::Matrix1(int** a, int** A) {
	for (int i = 1; i <= this->size; i++) {
		for (int j = 1; j <= this->size + 1; j++) {
			Control^ control = AdjacencyMatrix->GetControlFromPosition(j, i);
			if (TextBox^ textBox = dynamic_cast<TextBox^>(control)) {
				int value = Convert::ToInt32(textBox->Text->Trim());
				if (j == this->size + 1) {
					A[i - 1][j - 1] = value;
				}
				else {
					A[i - 1][j - 1] = value;
					a[i - 1][j - 1] = value;
				}
			}
		}
	}
}

inline bool MyForm::CheckTableContents1() {
	int num = 0;
	for (int i = 1; i <= this->size; i++) {
		for (int j = 1; j <= this->size; j++) {
			Control^ control = AdjacencyMatrix->GetControlFromPosition(j, i);
			if (TextBox^ textBox = dynamic_cast<TextBox^>(control)) {
				String^ text = textBox->Text->Trim();
				if (text != "0" && text != "1") {
					return false;
				}
			}
		}
	}
	for (int i = 1; i <= this->size; i++) {
		for (int j = 1; j <= this->size; j++) {
			Control^ control = AdjacencyMatrix->GetControlFromPosition(j, i);
			if (TextBox^ textBox = dynamic_cast<TextBox^>(control)) {
				String^ text = textBox->Text->Trim();
				if (text == "0") {
					num++;
				}
			}  
		}
	}
	if (num == this->size * (this->size - 1)) {
		return false;
	}
	else {
		return true;
	}
}

inline void MyForm::DrawGraph(int** array1) {
	this->label4->Location = System::Drawing::Point(20, (this->size + 1) * 50 + 180);
	this->label4->Show();
	this->GraphsForm->Location = System::Drawing::Point(20, (this->size + 1) * 50 + 215);
	this->GraphsForm->Width = 500;
	this->GraphsForm->Height = 500;
	this->GraphsForm->BringToFront();
	this->GraphsForm->Show();
	if (GraphsForm->Image == nullptr) {
		GraphsForm->Image = gcnew Bitmap(GraphsForm->Width, GraphsForm->Height);
	}
	Graphics^ g = Graphics::FromImage(GraphsForm->Image);
	g->Clear(SystemColors::ButtonHighlight);
	Pen^ pen = gcnew Pen(Color::Green);
	Brush^ inputBrush = gcnew SolidBrush(Color::Red);     
	Brush^ outputBrush = gcnew SolidBrush(Color::Black);  
	Brush^ defaultBrush = gcnew SolidBrush(Color::Yellow); 
	Brush^ textBrush = gcnew SolidBrush(Color::Black);

	array<bool>^ isInput = gcnew array<bool>(this->size + 1);
	array<bool>^ isOutput = gcnew array<bool>(this->size + 1);
	array<int>^ layers = gcnew array<int>(this->size + 1); 
	array<int>^ layerCounts = gcnew array<int>(this->size + 1); 
	array<int, 2>^ layerVertices = gcnew array<int, 2>(this->size + 1, this->size + 1);
	int maxLayer = 0;

	for (int i = 0; i < this->size + 1; i++) {
		isInput[i] = true;
		isOutput[i] = true;
		layers[i] = -1;
		layerCounts[i] = 0;
	}
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size + 1; j++) {
			if (array1[i][j] == 1) {
				isInput[j] = false; 
				isOutput[i] = false;
			}
		}
	}
	isOutput[this->size] = true;
	array<int>^ distToOutput = gcnew array<int>(this->size + 1);
	for (int i = 0; i < this->size + 1; i++) {
		distToOutput[i] = Int32::MaxValue;
	}
	for (int i = 0; i < this->size + 1; i++) {
		if (isOutput[i]) {
			distToOutput[i] = 0; 
			layers[i] = 0; 
			layerVertices[0, layerCounts[0]++] = i;
		}
	}
	bool changed = true;
	while (changed) {
		changed = false;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size + 1; j++) {
				if (array1[i][j] == 1 && distToOutput[j] != Int32::MaxValue) {
					if (distToOutput[i] > distToOutput[j] + 1) {
						distToOutput[i] = distToOutput[j] + 1;
						changed = true;
					}
				}
			}
		}
	}
	for (int i = 0; i < this->size + 1; i++) {
		if (distToOutput[i] != Int32::MaxValue) {
			layers[i] = distToOutput[i];
			layerVertices[distToOutput[i], layerCounts[distToOutput[i]]++] = i;
			maxLayer = Math::Max(maxLayer, distToOutput[i]);
		}
		else {
			layers[i] = maxLayer + 1; 
			layerVertices[maxLayer + 1, layerCounts[maxLayer + 1]++] = i;
			maxLayer = Math::Max(maxLayer, maxLayer + 1);
		}
	}
	array<int>^ newLayers = gcnew array<int>(this->size + 1);
	array<int>^ newLayerCounts = gcnew array<int>(this->size + 1);
	array<int, 2>^ newLayerVertices = gcnew array<int, 2>(this->size + 1, this->size + 1);
	for (int i = 0; i < this->size + 1; i++) {
		newLayerCounts[i] = 0;
	}
	for (int i = 0; i < this->size + 1; i++) {
		if (layers[i] != -1) {
			newLayers[i] = maxLayer - layers[i];
			newLayerVertices[newLayers[i], newLayerCounts[newLayers[i]]++] = i;
		}
	}
	layers = newLayers;
	layerCounts = newLayerCounts;
	layerVertices = newLayerVertices;
	int margin = 50;
	int xSpacing = maxLayer > 0 ? (GraphsForm->Width - 2 * margin) / maxLayer : 0;
	if (xSpacing > 100) xSpacing = 100;
	int maxVerticesInLayer = 0;
	for (int i = 0; i <= maxLayer; i++) {
		maxVerticesInLayer = Math::Max(maxVerticesInLayer, layerCounts[i]);
	}
	int ySpacing = maxVerticesInLayer > 1 ? (GraphsForm->Height - 2 * margin) / (maxVerticesInLayer - 1) : 0;
	if (ySpacing > 100) ySpacing = 100; 

	points = gcnew array<Point>(this->size + 1);
	for (int layer = 0; layer <= maxLayer; layer++) {
		int x = margin + layer * xSpacing;
		for (int k = 0; k < layerCounts[layer]; k++) {
			int i = layerVertices[layer, k];
			int y = margin + k * ySpacing;
			if (layerCounts[layer] == 1) y = GraphsForm->Height / 2;
			points[i] = Point(x, y);
			Brush^ vertexBrush = isOutput[i] ? outputBrush : (isInput[i] ? inputBrush : defaultBrush);
			g->FillEllipse(vertexBrush, x - 10, y - 10, 20, 20);
			g->DrawEllipse(pen, x - 10, y - 10, 20, 20);
			g->DrawString((i + 1 < this->size + 1) ? (i + 1).ToString() : (0).ToString(),
				gcnew System::Drawing::Font("Microsoft Sans Serif", 12), textBrush, (float)x + 10, (float)y - 10);
		}
	}
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size + 1; j++) {
			if (array1[i][j] == 1) {
				points_for_vectors = gcnew array<Point>(2);
				g->DrawLine(pen, points[i], points[j]);
				double angle = Math::Atan2(points[j].Y - points[i].Y, points[j].X - points[j].X);
				int arrowLength = 20;
				double arrowAngle = Math::PI / 6;
				int x1 = points[j].X - (int)(arrowLength * Math::Cos(angle + arrowAngle));
				int y1 = points[j].Y - (int)(arrowLength * Math::Sin(angle + arrowAngle));
				g->DrawLine(pen, points[j], Point(x1, y1));
				int x2 = points[j].X - (int)(arrowLength * Math::Cos(angle - arrowAngle));
				int y2 = points[j].Y - (int)(arrowLength * Math::Sin(angle - arrowAngle));
				g->DrawLine(pen, points[j], Point(x2, y2));
			}
		}
	}
}

inline void MyForm::FindTheDefinitions(int** A, int** new_array, int iter) {
	this->Rat_or_Not->Show();
	int k1 = 0, k2 = 0, k3 = 0, k4 = 0, NumOft4 = 0, t5 = 0, t6 = 0, r = 0;
	float kmo_mij = 0;
	int* t1 = new int[100]();
	int* t2 = new int[100]();
	int* t3 = new int[100]();
	int* t4 = new int[100]();
	int* t7 = new int[100]();
	float* kmo = new float[100]();
	int** C = new int* [100];
	for (int i = 0; i < 100; i++) {
		C[i] = new int[2]();
	}
	(40*this->size+2<350)?this->DefTable->Location = System::Drawing::Point(380, 35): this->DefTable->Location = System::Drawing::Point(80 + 40 * this->size + 2, 35);
	this->DefTable->AutoSize = true;
	this->DefTable->Show();
	this->DefTable->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16);
	this->DefTable->Controls->Clear();
	this->DefTable->ColumnCount = 6;
	this->DefTable->RowCount = 5;
	this->DefTable->ColumnStyles->Clear();
	this->DefTable->RowStyles->Clear();
	for (int j = 0; j <= 5; j++) {
		Label^ label = gcnew Label();
		label->AutoSize = true;
		label->Margin = System::Windows::Forms::Padding(15, 2, 0, 0);
		if (j == 0) {
			label->Text = "T";
			this->DefTable->SetColumn(label, j);
			this->DefTable->SetRow(label, 0);
			this->DefTable->Controls->Add(label);
			for (int i = 0; i < 4; i++) {
				Label^ label = gcnew Label();
				label->AutoSize = true;
				label->Margin = System::Windows::Forms::Padding(15, 2, 0, 0);
				label->Text = "t" + System::Convert::ToString(i + 1);
				this->DefTable->SetColumn(label, j);
				this->DefTable->SetRow(label, i + 1);
				this->DefTable->Controls->Add(label);
			}
		}
		else if (j == 1) {
			label->Text = "The tops";
			this->DefTable->SetColumn(label, j);
			this->DefTable->SetRow(label, 0);
			this->DefTable->Controls->Add(label);
		}
		else if (j == 2) {
			label->Text = "T and Km";
			this->DefTable->SetColumn(label, j);
			this->DefTable->SetRow(label, 0);
			this->DefTable->Controls->Add(label);
			for (int i = 0; i < 4; i++) {
				Label^ label = gcnew Label();
				label->AutoSize = true;
				label->Margin = System::Windows::Forms::Padding(15, 2, 0, 0);
				(i < 3) ? label->Text = "t" + System::Convert::ToString(i + 5) : label->Text = "Km";
				this->DefTable->SetColumn(label, j);
				this->DefTable->SetRow(label, i + 1);
				this->DefTable->Controls->Add(label);
			}
		}
		else if (j == 3) {
			label->Text = "Values";
			this->DefTable->SetColumn(label, j);
			this->DefTable->SetRow(label, 0);
			this->DefTable->Controls->Add(label);
		}
		else if (j == 4) {
			Label^ Names = gcnew Label();
			label->AutoSize = true;
			Label^ Kmo = gcnew Label();
			label->AutoSize = true;
			Label^ label = gcnew Label();
			label->AutoSize = true;
			Label^ Knk = gcnew Label();
			label->AutoSize = true;
			Label^ Kmo_mij = gcnew Label();
			label->AutoSize = true;
			Label^ Krk = gcnew Label();
			Krk->AutoSize = true;
			Names->Text = "K's";
			this->DefTable->SetColumn(Names, j);
			this->DefTable->SetRow(Names, 0);
			this->DefTable->Controls->Add(Names);
			Kmo->Text = "Kmo";
			this->DefTable->SetColumn(Kmo, j);
			this->DefTable->SetRow(Kmo, 1);
			this->DefTable->Controls->Add(Kmo);
			Knk->Text = "Knc";
			this->DefTable->SetColumn(Knk, j);
			this->DefTable->SetRow(Knk, 2);
			this->DefTable->Controls->Add(Knk);
			Kmo_mij->Text = "KmoMID";
			this->DefTable->SetColumn(Kmo_mij, j);
			this->DefTable->SetRow(Kmo_mij, 3);
			this->DefTable->Controls->Add(Kmo_mij);
			Krk->Text = "Kr";
			this->DefTable->SetColumn(Krk, j);
			this->DefTable->SetRow(Krk, 4);
			this->DefTable->Controls->Add(Krk);
		}
		else {
			label->Text = "Values";
			this->DefTable->SetColumn(label, j);
			this->DefTable->SetRow(label, 0);
			this->DefTable->Controls->Add(label);
		}
	}
	Label^ label1 = gcnew Label();
	label1->AutoSize = true;
	Label^ label2 = gcnew Label();
	label2->AutoSize = true;
	Label^ label3 = gcnew Label();
	label3->AutoSize = true;
	for (int i = 0; i < this->size; i++) {
		bool isSource = true;
		for (int j = 0; j < this->size; j++) {
			if (A[j][i] == 1) {
				isSource = false;
				break;
			}
		}
		if (isSource) {
			for (int j = 0; j < this->size; j++) {
				if (A[i][j] == 1) {
					t1[k1] = i + 1;
					if (!Duplicate(t1, k1, t1[k1])) {
						k1++;
					}
					break;
				}
			}
		}
		for (int j = 0; j < this->size + 1; j++) {
			for (int k = 0; k < this->size; k++) {
				if (A[i][j] == 1 && j != this->size && A[j][k] == 1) {
					t2[k2] = j + 1;
					if (Duplicate(t2, k2, t2[k2])) {
						continue;
					}
					k2++;
				}
			}
			if (A[i][j] == 1 && j == this->size) {
				t3[k3] = i + 1;
				k3++;
			}
		}
	}
	sort(t1, k1);
	sort(t2, k2);
	sort(t3, k3);
	for (int i = 0; i < k1; ++i) {
		(i != k1 - 1) ? label1->Text += System::Convert::ToString(t1[i]) + ", " : label1->Text += System::Convert::ToString(t1[i]) + " ";
	}
	for (int i = 0; i < k2; ++i) {
		(i != k2 - 1) ? label2->Text += System::Convert::ToString(t2[i]) + ", " : label2->Text += System::Convert::ToString(t2[i]) + " ";
	}
	for (int i = 0; i < k3; ++i) {
		(i != k3 - 1) ? label3->Text += System::Convert::ToString(t3[i]) + ", " : label3->Text += System::Convert::ToString(t3[i]) + " ";
	}
	Label^ label4 = gcnew Label();
	label4->AutoSize = true;
	Label^ T7 = gcnew Label();
	T7->AutoSize = true;
	Label^ KMO = gcnew Label();
	KMO->AutoSize = true;
	for (int j = 0; j < (2 + iter) * this->size; j++) {
		bool t = true;
		for (int i = 0; i < this->size; i++) {
			if (new_array[i][j] != 0) {
				t = false;
				break;
			}
		}
		if (!t) {
			continue;
		}
		else {
			NumOft4++;
		}
		if (j > 0 && j % this->size == 0) {
			if (k4 == 0) {
				NumOft4--;
			}
			t4[k4] = NumOft4;
			NumOft4 = 0;
			k4++;
		}
	}
	for (int i = 0; i < k4; i++) {
		(i != k4 - 1) ? label4->Text += System::Convert::ToString(i + 1 + "." + t4[i]) + ", " : label4->Text += System::Convert::ToString(i + 1 + "." + t4[i]) + " ";
	}
	for (int i = 0; i < k4; i++) {
		t7[i] = t4[i] - (i + 1);
		kmo[i] = (float)t7[i] / (float)t4[i];
		(i != k4 - 1) ? T7->Text += System::Convert::ToString(i + 1 + "." + t7[i]) + ", " : T7->Text += System::Convert::ToString(i + 1 + "." + t7[i]) + " ";
		(i != k4 - 1) ? KMO->Text += System::Convert::ToString(i + 1 + "." + kmo[i]) + "; " : KMO->Text += System::Convert::ToString(i + 1 + "." + kmo[i]) + " ";

	}
	Label^ KMOMIJ = gcnew Label();
	KMOMIJ->AutoSize = true;
	for (int i = 0; i < k4; i++) {
		kmo_mij += kmo[i];
	}
	KMOMIJ->Text += System::Convert::ToString(kmo_mij / (float)k4);
	Label^ T5 = gcnew Label();
	T5->AutoSize = true;
	int k = 0;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size + 1; j++) {
			if (A[i][j] == 1 && j < this->size) {
				C[k][0] = i + 1;
				C[k][1] = j + 1;
				r++;
				k++;
			}
			if (A[i][j] == 1 && j == this->size) {
				C[k][0] = i + 1;
				C[k][1] = 0;
				k++;
			}
		}
	}
	for (int i = 0; i < k; i++) {
		int start = C[i][0];
		int end = C[i][1];
		bool intermediate_start = true;
		bool intermediate_end = false;
		for (int j = 0; j < k1; j++) {
			if (start == t1[j]) {
				intermediate_start = false;
				break;
			}
		}
		for (int j = 0; j < k2; j++) {
			if (end == t2[j]) {
				intermediate_end = true;
				break;
			}
		}
		for (int j = 0; j < k3; j++) {
			if (start == t3[j] || end == t3[j]) {
				intermediate_start = false;
				intermediate_end = false;
				break;
			}
		}
		if (intermediate_start && intermediate_end) {
			t5++;
		}
	}
	T5->Text = System::Convert::ToString(t5);
	Label^ T6 = gcnew Label();
	T6->AutoSize = true;
	for (int j = 0; j < k; j++) {
		if (C[j][1] == 0) {
			t3[k3++] = C[j][0];
			for (int i = 0; i < k; i++) {
				if (i == j) continue;
				if (C[j][0] == C[i][0] && C[i][1] != 0) {
					t6++;
				}
			}
		}
	}
	T6->Text = System::Convert::ToString(t6);
	Label^ KM = gcnew Label();
	KM->AutoSize = true;
	KM->Text = System::Convert::ToString((float)k2 / (float)this->size);
	Label^ KNK = gcnew Label();
	KNK->AutoSize = true;
	KNK->Text = System::Convert::ToString((double)t5 / (double)r);
	Label^ KRK = gcnew Label();
	KRK->AutoSize = true;
	KRK->Text = System::Convert::ToString((float)(2 * t6) / (float)(k3 * (k3 - 1)));
	Rat_or_Not->AutoSize = true;
	(40 * this->size + 2 < 350) ?Rat_or_Not->Location=System::Drawing::Point(380, 200) : Rat_or_Not->Location = System::Drawing::Point(80 + 40 * this->size + 2, 200);
	(fabs(((float)k2 / (float)this->size) - kmo_mij) < 0.01) ? Rat_or_Not->Text = "The graph is rationally constructed" : Rat_or_Not->Text = "The graph is not rationally constructed";
	//
	this->DefTable->SetColumn(label1, 1);
	this->DefTable->SetRow(label1, 1);
	this->DefTable->Controls->Add(label1);
	//
	this->DefTable->SetColumn(label2, 1);
	this->DefTable->SetRow(label2, 2);
	this->DefTable->Controls->Add(label2);
	//
	this->DefTable->SetColumn(label3, 1);
	this->DefTable->SetRow(label3, 3);
	this->DefTable->Controls->Add(label3);
	//
	this->DefTable->SetColumn(label4, 1);
	this->DefTable->SetRow(label4, 4);
	this->DefTable->Controls->Add(label4);
	//
	this->DefTable->SetColumn(T5, 3);
	this->DefTable->SetRow(T5, 1);
	this->DefTable->Controls->Add(T5);
	//
	this->DefTable->SetColumn(T6, 3);
	this->DefTable->SetRow(T6, 2);
	this->DefTable->Controls->Add(T6);
	//
	this->DefTable->SetColumn(T7, 3);
	this->DefTable->SetRow(T7, 3);
	this->DefTable->Controls->Add(T7);
	//
	this->DefTable->SetColumn(KM, 3);
	this->DefTable->SetRow(KM, 4);
	this->DefTable->Controls->Add(KM);
	//
	this->DefTable->SetColumn(KMO, 5);
	this->DefTable->SetRow(KMO, 1);
	this->DefTable->Controls->Add(KMO);
	//
	this->DefTable->SetColumn(KNK, 5);
	this->DefTable->SetRow(KNK, 2);
	this->DefTable->Controls->Add(KNK);
	//
	this->DefTable->SetColumn(KMOMIJ, 5);
	this->DefTable->SetRow(KMOMIJ, 3);
	this->DefTable->Controls->Add(KMOMIJ);
	//
	this->DefTable->SetColumn(KMOMIJ, 5);
	this->DefTable->SetRow(KMOMIJ, 3);
	this->DefTable->Controls->Add(KMOMIJ);
	//
	this->DefTable->SetColumn(KRK, 5);
	this->DefTable->SetRow(KRK, 4);
	this->DefTable->Controls->Add(KRK);
	//
	delete[] t1;
	delete[] t2;
	delete[] t3;
	delete[] t4;
	delete[] t7;
	delete[] kmo;
	for (int i = 0; i < 100; i++) {
		delete[] C[i];
	}
	delete[] C;
}

inline void MyForm::Iterations1(int iter_count, int** new_array) {
	this->IterationsTable->Location = System::Drawing::Point(16, 160 + size * 25);
	this->IterationsTable->Show();
	this->IterationsTable->AutoSize = true;
	this->IterationsTable->Controls->Clear();
	this->IterationsTable->ColumnCount = iter_count;
	this->IterationsTable->RowCount = 1;
	this->IterationsTable->ColumnStyles->Clear();
	this->IterationsTable->RowStyles->Clear();
	for (int t = 0; t < iter_count; t++) {
		TableLayoutPanel^ table = gcnew TableLayoutPanel();
		table->ColumnCount = this->size + 1;
		table->RowCount = this->size + 1;
		table->CellBorderStyle = TableLayoutPanelCellBorderStyle::Single;
		table->AutoSize = true;
		for (int i = 0; i <= this->size; i++) {
			for (int j = 0; j <= this->size; j++) {
				Label^ label = gcnew Label();
				label->AutoSize = true;
				label->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16);
				label->TextAlign = ContentAlignment::MiddleCenter;
				if (i == 0 && j == 0) {
					label->Text = "A^" + (t + 2);
					label->BackColor = System::Drawing::Color::Gray;
				}
				else if (i == 0) {
					label->Text = System::Convert::ToString(j);
					label->BackColor = System::Drawing::Color::Gray;

				}
				else if (j == 0) {
					label->Text = System::Convert::ToString(i);
					label->BackColor = System::Drawing::Color::Gray;
				}
				else {
					label->Text = System::Convert::ToString(new_array[i - 1][this->size * (t + 1) + (j - 1)]);
				}
				table->Controls->Add(label, j, i);
			}
		}
		this->IterationsTable->Controls->Add(table, t, 0);
	}
}

inline void MyForm::SigmaMatrix(int iter_count, int** a, int** new_array) {
	this->label5->Location = System::Drawing::Point(550, (this->size + 1) * 50 + 180);
	this->label5->Show();
	const int size1 = this->size;
	int** sigma = new int* [size1];
	for (int i = 0; i < size1; ++i) {
		sigma[i] = new int[size1];
	}
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size1; j++) {
			sigma[i][j] = 0;
		}
	}
	int i, j, count = 0;
	while (count < iter_count) {
		for (i = 0; i < size1; i++) {
			for (j = 0; j < size1; j++) {
				sigma[i][j] += new_array[i][size1 * count + j];
			}
		}
		count++;
	}
	this->SigmaTable->Controls->Clear();
	this->SigmaTable->Show();
	this->SigmaTable->AutoSize = true;
	this->SigmaTable->RowCount = this->size + 1;
	this->SigmaTable->ColumnCount = this->size + 1;
	this->SigmaTable->Location = System::Drawing::Point(550, (size1 + 1) * 50 + 215);
	for (int i = 0; i <= size1; i++) {
		for (int j = 0; j <= size1; j++) {
			Label^ label = gcnew Label();
			label->AutoSize = true;
			label->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16);
			label->TextAlign = ContentAlignment::MiddleCenter;
			if (i == 0 && j == 0) {
				label->Text = "S";
				label->BackColor = System::Drawing::Color::Gray;

			}
			else if (i == 0) {
				label->Text = System::Convert::ToString(j);
				label->BackColor = System::Drawing::Color::Gray;

			}
			else if (j == 0) {
				label->Text = System::Convert::ToString(i);
				label->BackColor = System::Drawing::Color::Gray;
			}
			else {
				label->Text = System::Convert::ToString(sigma[i - 1][j - 1]);
			}
			this->SigmaTable->Controls->Add(label, j, i);
		}
	}
	for (int i = 0; i < size1; ++i) {
		delete[] sigma[i];
	}
	delete[] sigma;
}

//The shortest path

inline void MyForm::Matrix2(int** a) {
	for (int i = 1; i <= this->size; i++) {
		for (int j = 1; j <= this->size + 1; j++) {
			Control^ control = AdjacencyMatrix->GetControlFromPosition(j, i);
			if (TextBox^ textBox = dynamic_cast<TextBox^>(control)) {
				int value = Convert::ToInt32(textBox->Text->Trim());
				a[i - 1][j - 1] = value;
			}
		}
	}
}

inline bool MyForm::CheckTableContents2() {
	int num = 0;
	for (int i = 1; i <= this->size; i++) {
		for (int j = 1; j <= this->size; j++) {
			Control^ control = AdjacencyMatrix->GetControlFromPosition(j, i);
			if (TextBox^ textBox = dynamic_cast<TextBox^>(control)) {
				String^ text = textBox->Text->Trim();
				if (text == "0") {
					num++;
				}
			}
		}
	}
	if (num == (this->size * (this->size - 1)) / 2) {
		return false;
	}
	else {
		return true;
	}
}

inline void MyForm::Iterations2(int** a, int** result) {
	this->IterationsTable->Location = System::Drawing::Point(80 + 40 * this->size + 2, 60);
	this->IterationsTable->Show();
	this->IterationsTable->AutoSize = true;
	this->IterationsTable->Controls->Clear();
	this->IterationsTable->ColumnStyles->Clear();
	this->IterationsTable->RowStyles->Clear();
	int totalTables = this->size;
	int columnCount = static_cast<int>(sqrt(totalTables));
	int rowCount = static_cast<int>(static_cast<double>(totalTables) / columnCount);
	this->IterationsTable->ColumnCount = columnCount;
	this->IterationsTable->RowCount = rowCount;
	for (int k = 0; k < size; k++) {
		TableLayoutPanel^ table = gcnew TableLayoutPanel();
		table->ColumnCount = this->size + 1;
		table->RowCount = this->size + 1;
		table->CellBorderStyle = TableLayoutPanelCellBorderStyle::Single;
		table->AutoSize = true;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (a[i][k] != 0 && a[k][j] != 0) {
					if (a[i][k] + a[k][j] < a[i][j] || a[i][j] == 0) {
						a[i][j] = a[i][k] + a[k][j];
						result[i][j] = k;
					}
				}
			}
		}
		for (int i = 0; i <= this->size; i++) {
			for (int j = 0; j <= this->size; j++) {
				Label^ label = gcnew Label();
				label->AutoSize = true;
				label->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16);
				label->TextAlign = ContentAlignment::MiddleCenter;
				if (i == 0 && j == 0) {
					label->Text = "I^" + (k + 1);
					label->BackColor = System::Drawing::Color::Gray;
				}
				else if (i == 0) {
					label->Text = System::Convert::ToString(j);
					label->BackColor = System::Drawing::Color::Gray;
				}
				else if (j == 0) {
					label->Text = System::Convert::ToString(i);
					label->BackColor = System::Drawing::Color::Gray;
				}
				else {
					label->Text = System::Convert::ToString(a[i - 1][j - 1]);
				}
				table->Controls->Add(label, j, i);
			}
		}
		int row = k / columnCount;
		int col = k % columnCount;
		this->IterationsTable->Controls->Add(table, col, row);
	}
}