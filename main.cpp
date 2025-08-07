#include <wx/wx.h> 
#include "triangle.xpm"

// Основной класс окна приложения
class MathFrame : public wxFrame {
public:
	MathFrame(); // Конструктор
protected:
	void OnMouseDown(wxMouseEvent& event); // Обработчик нажатия мыши
	void OnMouseMove(wxMouseEvent& event); // Обработчик движения мыши
	void SetWindowShape(); // Установка формы окна
	void OnWindowCreate(wxWindowCreateEvent& event); // Обработчик создания окна
	void OnPaint(wxPaintEvent& event); // Обработчик перерисовки окна

	wxBitmap m_bmp; // Хранит изображение треугольника
	wxPoint m_delta; // Смещение мыши при перетаскивании
	bool m_hasShape; // Флаг, указывающий, установлена ли форма окна

	wxDECLARE_EVENT_TABLE(); // Таблица событий для обработки событий мыши и перерисовки окна
};

// Основной класс приложения
class MathApp : public wxApp {
public:
	virtual bool OnInit() override { // Инициализация приложения
		MathFrame* frame = new MathFrame(); // Создание главного окна
		frame->Show(true); // Отображение окна
		frame->Centre(); // Центрирование окна на экране
		return true; // Возвращаем true, чтобы приложение продолжало работать
	}
};

wxIMPLEMENT_APP(MathApp); // Реализация приложения

// Таблица привязки событий к обработчикам
wxBEGIN_EVENT_TABLE(MathFrame, wxFrame) // Таблица событий для MathFrame
EVT_LEFT_DOWN(MathFrame::OnMouseDown) // Обработчик нажатия левой кнопки мыши
EVT_MOTION(MathFrame::OnMouseMove) // Обработчик движения мыши
EVT_PAINT(MathFrame::OnPaint) // Обработчик перерисовки окна
#ifdef __WXGTK__ 
EVT_WINDOW_CREATE(MathFrame::OnWindowCreate) // Обработчик создания окна для GTK
#endif
wxEND_EVENT_TABLE()
// Конец таблицы событий

// Конструктор окна MathFrame
MathFrame::MathFrame()
	: wxFrame(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(492, 139),
		wxFRAME_SHAPED | wxFRAME_NO_TASKBAR | wxSIMPLE_BORDER | wxSTAY_ON_TOP)
{
	m_hasShape = false; // Изначально форма окна не установлена
	m_bmp = wxBitmap(triangle_xpm); SetSize(wxSize(m_bmp.
		GetWidth(), m_bmp.GetHeight())); // Устанавливаем размер окна равным размеру изображения треугольника

#ifndef __WXGTK__ 
	SetWindowShape(); // Устанавливаем форму окна, если не GTK
#endif 
}

// Обработчик создания окна
void MathFrame::OnWindowCreate(wxWindowCreateEvent& WXUNUSED(evt)) {
	SetWindowShape();
}

// Установка формы окна на основе изображения треугольника
void MathFrame::SetWindowShape() {
	wxRegion region(m_bmp, *wxWHITE);  // Делаем белый цвет прозрачным
	SetShape(region);
}

// Обработчик нажатия мыши
void MathFrame::OnMouseDown(wxMouseEvent& evt) {
	m_delta = evt.GetPosition();  // Фиксируем начальную точку
}

// Обработчик движения мыши
void MathFrame::OnMouseMove(wxMouseEvent& evt) {
	if (evt.Dragging() && evt.LeftIsDown()) {
		wxPoint pos = ClientToScreen(evt.GetPosition());
		Move(pos - m_delta);
	}
}

// Обработчик перерисовки окна
void MathFrame::OnPaint(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	dc.DrawBitmap(m_bmp, 0, 0, true);
}
