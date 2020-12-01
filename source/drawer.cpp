#include <drawer.hpp>

void drawer::cicle(const std::vector<double>& x_vec_, const std::vector<double>& y_vec_) {
    x_vec = x_vec_;
    y_vec = y_vec_;
    sf::RenderWindow window(sf::VideoMode(x_size, y_size), "Function plot");
    set_limits();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        draw_plate(window);
        draw_curve(window);
        window.display();
    }
}

void drawer::set_limits() {
    for (int i = 0; i < x_vec.size(); i++) {
        coordinates.push_back(std::make_pair(x_vec[i], y_vec[i]));
    }

    auto temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return abs(a.first) < abs(b.first);
        });
    int mod_x = abs(ceil((*temp).first));

    temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return abs(a.second) < abs(b.second);
        });
    int mod_y = abs(ceil((*temp).second));

    if (mod_y > mod_x) {
        while (mod_y % 10 != 0)
        {
            mod_y++;
        }
        if (mod_y == 0) {
            limit_x1 = limit_y1 = 5;
        }
        limit_x1 = limit_y1 = mod_y;
        limit_x0 = limit_y0 = -mod_y;
    }
    else {
        while (mod_x % 10 != 0)
        {
            mod_x++;
        }
        if (mod_x == 0) {
            limit_x1 = limit_y1 = 5;
        }
        limit_x1 = limit_y1 = mod_x;
        limit_x0 = limit_y0 = -mod_x;
    }
}

void drawer::draw_plate(sf::RenderWindow& window) {
    window.clear(sf::Color(255, 255, 255, 0));
    //Оси
    sf::RectangleShape line;
    line.setFillColor(sf::Color(0, 0, 0));
    //Вертикаль Y
    line.setPosition(0, new_center_y);
    line.setSize(sf::Vector2f(x_size, 4));
    window.draw(line);
    //Горизонталь X
    line.setPosition(new_center_x, 0);
    line.setSize(sf::Vector2f(4, y_size));
    window.draw(line);

    sf::Font font;
    if (!font.loadFromFile("D:\\Github\\arial.ttf")) {
        std::cout << "Ошибка чтения шрифта" << std::endl;
    }

    sf::Text text;
    text.setCharacterSize(10);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setFont(font);

    double count_marker_y = limit_y1 - limit_y0 / step_y;
    double len_axis_y = y_size;
    for (double u = 0; u <= count_marker_y; u++) {
        //Текст
        int var = limit_y0 + (count_marker_y - u) * step_y;
        std::string s = std::to_string(var);
        text.setString(s);
        text.setPosition(new_center_x + 15, len_axis_y / count_marker_y * u - 10);
        window.draw(text);

        line.setFillColor(sf::Color(0, 0, 0));
        //Горизонтальные
        line.setPosition(0, len_axis_y / count_marker_y * u);
        line.setSize(sf::Vector2f(x_size, 1));
        window.draw(line);
    }

    //Разметка горизонтальной оси
    double count_marker_x = limit_x1 - limit_x0 / step_x;
    double len_axis_x = x_size;
    for (double u = 0; u <= count_marker_x; ++u) {
        //Текст
        int var = limit_x0 + u * step_x;
        std::string s = std::to_string(var);
        text.setString(s);
        text.setPosition(len_axis_x / count_marker_x * u, new_center_y + 15);
        window.draw(text);
        //Вспомогательные линии сетки
        //вертикальные
        line.setPosition(len_axis_x / count_marker_x * u, 0);
        line.setSize(sf::Vector2f(1, y_size));
        window.draw(line);
    }

    //X
    text.setCharacterSize(20);
    text.setString("X");
    text.setPosition(x_size - 15, new_center_y - 25);
    window.draw(text);
    //Y
    text.setString("Y");
    text.setPosition(new_center_x - 15, 0);
    window.draw(text);
}

void drawer::draw_curve(sf::RenderWindow& window) {
    calculate_scaling();
    sf::Color color_graph(255, 0, 0);
    for (int i = 0; i < coordinates.size(); i++) {
        double point_x = (coordinates[i].first - limit_x0) * scaling_factor_x;
        double point_y = y_size + (limit_y0 - coordinates[i].second) * scaling_factor_y;
        sf::CircleShape shape(marker_size);
        shape.setPosition(point_x - marker_size, point_y - marker_size);
        shape.setFillColor(color_graph);
        window.draw(shape);
        if (i > 0) {
            sf::VertexArray lines(sf::LinesStrip, 2);
            lines[0].position = sf::Vector2f(point_x, point_y);
            lines[0].color = sf::Color::Red;
            lines[1].position = sf::Vector2f((coordinates[i - 1].first - limit_x0) * scaling_factor_x,
                y_size + (limit_y0 - coordinates[i - 1].second) * scaling_factor_y);
            lines[1].color = sf::Color::Red;
            window.draw(lines);
        }
    }
}

void drawer::calculate_scaling() {
    scaling_factor_x = (x_size) / (limit_x1 - limit_x0);
    scaling_factor_y = (y_size) / (limit_y1 - limit_y0);
}

/*void drawer::set_limits() {
    auto temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return abs(a.first) < abs(b.first);
        });
    double x_max = (*temp).first;

    temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return abs(a.second) < abs(b.second);
        });
    double y_max = ceil((*temp).second);

    temp = std::min_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return abs(a.second) > abs(b.second);
        });
    double x_min = (*temp).first;

    temp = std::min_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return abs(a.second) > abs(b.second);
        });
    double y_min = floor((*temp).second);
}

void drawer::calculate_step() {
    step_x = (x_max - x_min) / (coordinates.size() - 1);
    step_y = (y_max - y_min) / (coordinates.size() - 1);
}

void drawer::scaled_vectors() {
    for (int i = 0; i < x_vec.size(); i++) {
        x_vec_scaled.push_back(x_vec[i] + step_x);
    }
    for (int i = 0; i < y_vec.size(); i++) {
        y_vec_scaled.push_back(y_vec[i] + step_y);
    }
}

void drawer::calculate_scaling() {
    scaling_factor_x = (x_max - x_min) / x_size;
    scaling_factor_y = (y_max - y_min) / y_size;
} */

