#include <Siv3D.hpp>

void Main() {
    Window::SetTitle(U"2-Chordal Ring Visualizer");
   
    Window::SetStyle(WindowStyle::Sizable);
    Scene::SetScaleMode(ScaleMode::ResizeFill);

    TextEditState N, d1, d2, M, Ea, Eb;
    int32 n, d_1, d_2, m;
    bool flag1 = false, col = false, mode = false, grab = false;
    
    Scene::SetBackground(ColorF(1, 1, 1, 1));
    ColorF c(0, 0, 0, 1), white(1, 1, 1, 1), black(0, 0, 0, 1);

    double r = 200.0;
    double dot = 10.0;
    double line_w = 4.0;
    const double M_PI = 3.14159265358979;

    const Font font(50);
    Array<Vec2> Edges;

    double cen_x = 400, cen_y = 300;

    while (System::Update()) {
        Circle circle(cen_x, cen_y, r / 5);
        if (circle.mouseOver()) {
            circle.draw(Palette::Skyblue);
        }

        if (grab)
        {
            cen_x += Cursor::Delta().x;
            cen_y += Cursor::Delta().y;
        }

        if (circle.leftClicked()) // 円を左クリックしたら
        {
            grab = true;
        }
        else if (MouseL.up()) // マウスの左ボタンが離されたら
        {
            grab = false;
        }

        if (grab || circle.mouseOver())
        {
            Cursor::RequestStyle(CursorStyle::Hand);
        }

        if (SimpleGUI::Button(U"Color", Vec2(40, 70), 60))
        {
            if (col) {
                Scene::SetBackground(white);
                c = black;
            }
            else {
                Scene::SetBackground(black);
                c = white;
            }
            col ^= 1;
        }

        SimpleGUI::Slider(U"Edge", line_w, 0.1, 10.0, Vec2(500, 10), 60, 200);
        SimpleGUI::Slider(U"Node", dot, 0.5, 50.0, Vec2(500, 40), 60, 200);
        SimpleGUI::Slider(U"Graph", r, 1.0, 400.0, Vec2(500, 70), 60, 200);

        if (SimpleGUI::Button(U"Mode", Vec2(40, 120), 60)) {
            mode ^= 1;
            flag1 = false;
        }

        Array<Vec2> node;

        if (mode) {
            SimpleGUI::TextBox(N, Vec2(40, 20), 50);
            SimpleGUI::TextBox(Ea, Vec2(40, 160), 50);
            SimpleGUI::TextBox(Eb, Vec2(40, 200), 50);

            if (SimpleGUI::Button(U"Clear", Vec2(220, 20), 60)) {
                N.clear();
                M.clear();
                Edges.clear();
                flag1 = false;
            }

            if (SimpleGUI::Button(U"Draw", Vec2(300, 20), 60)) {
                n = Parse<int32>(N.text);
                Edges.clear();
                flag1 = true;
            }

            if (!flag1) continue;

            for (int i = 0; i < n; i++) {
                node << Vec2(r * sin(M_PI * 2 * i / n) + cen_x, -r * cos(M_PI * 2 * i / n) + cen_y);
                Circle(node[i], dot).draw(c);
            }

            if (SimpleGUI::Button(U"add_edge", Vec2(40, 240), 100)) {
                Edges << Vec2(Parse<int32>(Ea.text), Parse<int32>(Eb.text));
            }

            for (auto& edge : Edges) {
                Line(node[edge.x], node[edge.y]).draw(line_w, c);
            }
        }
        else {
            SimpleGUI::TextBox(N, Vec2(40, 20), 50);
            SimpleGUI::TextBox(d1, Vec2(100, 20), 30);
            SimpleGUI::TextBox(d2, Vec2(150, 20), 30);

            if (SimpleGUI::Button(U"Clear", Vec2(220, 20), 60)) {
                N.clear();
                d1.clear();
                d2.clear();
                flag1 = false;
            }

            if (SimpleGUI::Button(U"Draw", Vec2(300, 20), 60)) {
                n = Parse<int32>(N.text);
                d_1 = Parse<int32>(d1.text);
                d_2 = Parse<int32>(d2.text);
                flag1 = true;
            }

            if (!flag1) continue;

            for (int i = 0; i < n; i++) {
                node << Vec2(r * sin(M_PI * 2 * i / n) + cen_x, -r * cos(M_PI * 2 * i / n) + cen_y);
                Circle(node[i], dot).draw(c);
           }

            for (int i = 0; i < n; i++) {
                Line(node[i], node[(i + 1) % n]).draw(line_w, c);
                Line(node[i], node[(i + d_1) % n]).draw(line_w, c);
                Line(node[i], node[(i + d_2) % n]).draw(line_w, c);
            }
        }
    }
}
