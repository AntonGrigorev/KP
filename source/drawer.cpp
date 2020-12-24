#include <drawer.hpp>

void drawer::cicle(const std::vector<double>& x_vec_, const std::vector<double>& y_vec_) {
    x_vec = x_vec_;
    y_vec = y_vec_;
    for (int i = 0; i < x_vec.size(); i++) {
        coordinates.push_back(std::make_pair(x_vec[i], y_vec[i]));
    }
    window.create(sf::VideoMode(x_size, y_size), "Function plot");
    if (linear_x == true && linear_y == true) {
        set_count_marker_x_linear();
        set_count_marker_y_linear();
        set_limit_x_lin();
        set_limit_y_lin();
        set_step_lin_x();
        set_step_lin_y();
        calculate_scaling_lin_x();
        calculate_scaling_lin_y();
    }
    else if (log_x == true && log_y == true) {
        set_count_marker_x_log();
        set_count_marker_y_log();
        set_limit_x_log();
        set_limit_y_log();
        set_step_log_x();
        set_step_log_y();
    }
    else if (linear_x == true && log_y == true) {
        set_count_marker_x_linear();
        set_count_marker_y_log();
        set_limit_x_lin();
        set_limit_y_log();
        set_step_lin_x();
        set_step_log_y();
        calculate_scaling_lin_x();
    }
    else {
        set_count_marker_x_log();
        set_count_marker_y_linear();
        set_limit_x_log();
        set_limit_y_lin();
        set_step_log_x();
        set_step_lin_y();
        calculate_scaling_lin_y();
    }

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

void drawer::set_step_lin_x() {
    step_x_lin = (limit_x1 - limit_x0) / count_marker_x;
}

void drawer::set_step_lin_y() {
    step_y_lin = (limit_y1 - limit_y0) / count_marker_y;
}

void drawer::set_step_log_x() {
    for (double i = 0; i < step_x_log.size(); i++) {
        step_x_log[i] = i;
        if (i > 1) {
            step_x_log[i] = step_x_log[i - 1] * 10;
        }
    }
}

void drawer::set_step_log_y() {
    for (double i = 0; i < step_y_log.size(); i++) {
        step_y_log[i] = i;
        if (i > 1) {
            step_y_log[i] = step_y_log[i - 1] * 10;
        }
    }
}

void drawer::set_count_marker_x_linear() {
    count_marker_x = 20;
}

void drawer::set_count_marker_y_linear() {
    count_marker_y = 20;
}

void drawer::set_count_marker_x_log() {
    count_marker_x = 6;
}

void drawer::set_count_marker_y_log() {
    count_marker_y = 6;
}

void drawer::set_limit_x_lin() {
    auto temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    double max_x = std::ceil((*temp).first * 1000) / 1000;
    max_x += 0.05 * max_x;

    temp = std::min_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    double min_x = std::floor((*temp).first * 1000) / 1000;
    min_x += 0.05 * min_x;

    if (abs(max_x) > abs(min_x)) {
        limit_x0 = -max_x;
        limit_x1 = max_x;
    }
    else {
        limit_x0 = min_x;
        limit_x1 = -min_x;
    }
}

void drawer::set_limit_y_lin() {
    auto temp = std::max_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    double max_y = std::ceil((*temp).second * 1000) / 1000;
    max_y += 0.05 * max_y;

    temp = std::min_element(coordinates.begin(), coordinates.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    double min_y = std::floor((*temp).second * 1000) / 1000;
    min_y += 0.05 * min_y;

    if (abs(max_y) > abs(min_y)) {
        limit_y0 = -max_y;
        limit_y1 = max_y;
    }
    else {
        limit_y0 = min_y;
        limit_y1 = -min_y;
    }
}

void drawer::set_limit_x_log() {
    limit_x1 = 100;
    limit_x0 = -100;
}

void drawer::set_limit_y_log() {
    limit_y1 = 100;
    limit_y0 = -100;
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
    if (!font.loadFromFile("..\\..\\..\\files\\font\\arial.ttf")) {
        std::cout << "Font reading error" << std::endl;
    }

    sf::Text text;
    text.setCharacterSize(10);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setFont(font);

    double len_axis_y = y_size;
    for (int u = 0; u <= count_marker_y; u++) {
        //Текст
        if (linear_y == true) {
            text.setString(std::to_string(limit_y1 - u * step_y_lin).substr(0, std::to_string(limit_y1 - u * step_y_lin).find(".") + 2 + 1));
        }
        else {
            if (log_y == true) {
                if (u < count_marker_y / 2) {
                    text.setString(std::to_string(step_y_log[count_marker_y / 2 - u]));
                }
                else {
                    text.setString(std::to_string(-step_y_log[u - count_marker_y / 2]));
                }
            }
        }
        //text.setString(std::to_string(limit_y1 - u * step_y_lin));
        text.setPosition(new_center_x + 15, len_axis_y / count_marker_y * u - 10);
        window.draw(text);

        line.setFillColor(sf::Color(0, 0, 0));
        //Горизонтальные
        line.setPosition(0, len_axis_y / count_marker_y * u);
        line.setSize(sf::Vector2f(x_size, 1));
        window.draw(line);
    }

    //Разметка горизонтальной оси
    double len_axis_x = x_size;
    for (int u = 0; u <= count_marker_x; u++) {
        //Текст
        if (linear_x == true) {
            text.setString(std::to_string(limit_x0 + u * step_x_lin).substr(0, std::to_string(limit_x0 + u * step_x_lin).find(".") + 2 + 1));
        }
        else {
            if (log_x == true) {
                if (u < count_marker_x / 2) {
                    text.setString(std::to_string(-step_x_log[count_marker_x / 2 - u]));
                }
                else {
                    text.setString(std::to_string(step_x_log[u - count_marker_x / 2]));
                }
            }
        }
        //text.setString(std::to_string(limit_x0 + u * step_x_lin));
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
    sf::Color color_graph(255, 0, 0);
    double point_x = 0, point_y = 0;
    for (int i = 0; i < coordinates.size(); i++) {
        if (linear_x == true && linear_y == true) {
            point_x = calculate_point_x_lin(coordinates, i);
            point_y = calculate_point_y_lin(coordinates, i);
        }
        else if (log_x == true && log_y == true) {
            point_x = calculate_point_x_log(coordinates, i);
            point_y = calculate_point_y_log(coordinates, i);
        }
        else if (linear_x == true && log_y == true) {
            point_x = calculate_point_x_lin(coordinates, i);
            point_y = calculate_point_y_log(coordinates, i);
        }
        else {
            point_x = calculate_point_x_log(coordinates, i);
            point_y = calculate_point_y_lin(coordinates, i);
        }
        sf::CircleShape shape(marker_size);
        shape.setPosition(point_x - marker_size, point_y - marker_size);
        shape.setFillColor(color_graph);
        window.draw(shape);
        if (i > 0) {
            sf::VertexArray lines(sf::LinesStrip, 2);
            lines[0].position = sf::Vector2f(point_x, point_y);
            lines[0].color = sf::Color::Red;
            if (linear_x == true && linear_y == true) {
                lines[1].position = sf::Vector2f(calculate_point_x_lin(coordinates, i - 1),
                    calculate_point_y_lin(coordinates, i - 1));
            }
            else if (log_x == true && log_y == true) {
                lines[1].position = sf::Vector2f(calculate_point_x_log(coordinates, i - 1),
                    calculate_point_y_log(coordinates, i - 1));
            }
            else if (linear_x == true && log_y == true) {
                lines[1].position = sf::Vector2f(calculate_point_x_lin(coordinates, i - 1),
                    calculate_point_y_log(coordinates, i - 1));
            }
            else {
                lines[1].position = sf::Vector2f(calculate_point_x_log(coordinates, i - 1),
                    calculate_point_y_lin(coordinates, i - 1));
            }
            lines[1].color = sf::Color::Red;
            window.draw(lines);
        }

    }
}

//Точки в линейном и логарифмическом маштабе
double drawer::calculate_point_x_lin(const std::vector<std::pair<double, double>>& coordinates, const int& i) {
    return (coordinates[i].first - limit_x0) * scaling_factor_x;
}

double drawer::calculate_point_y_lin(const std::vector<std::pair<double, double>>& coordinates, const int& i) {
    return y_size + (limit_y0 - coordinates[i].second) * scaling_factor_y;
}

double drawer::calculate_point_x_log(const std::vector<std::pair<double, double>>& coordinates, const int& i) {
    double min = 0, max = 0, start = 0;
    for (int u = 1; u < step_x_log.size(); u++) {
        if (step_x_log[u] > abs(std::log10(coordinates[i].first))) {
            max = step_x_log[u];
            min = step_x_log[u - 1];
            if (coordinates[i].first > 1) {
                start = x_size / count_marker_x * (u - 1 + count_marker_x / 2);
            }
            else {
                start = x_size / count_marker_x * (count_marker_y / 2 + 1 - u);
            }
            break;
        }
    }
    calculate_scaling_log_x(max, min);
    return start + (std::log10(coordinates[i].first) - min) * scaling_factor_x;
}

double drawer::calculate_point_y_log(const std::vector<std::pair<double, double>>& coordinates, const int& i) {
    double min = 0, max = 0, start = 0;
    for (int u = 1; u < step_y_log.size(); u++) {
        if (step_y_log[u] > abs(std::log10(coordinates[i].second))) {
            max = step_y_log[u];
            min = step_y_log[u - 1];
            if (coordinates[i].second >= 1) {
                start = y_size / count_marker_y * (count_marker_y / 2 - u);
            }
            else {
                start = y_size / count_marker_y * (count_marker_y / 2 + u - 2);
            }
            break;
        }
    }
    calculate_scaling_log_y(max, min);
    return start + (max - std::log10(coordinates[i].second)) * scaling_factor_y;
}

void drawer::calculate_scaling_lin_x() {
    scaling_factor_x = (x_size) / (limit_x1 - limit_x0);
}

void drawer::calculate_scaling_lin_y() {
    scaling_factor_y = (y_size) / (limit_y1 - limit_y0);
}

void drawer::calculate_scaling_log_x(const double& max, const double& min) {
    scaling_factor_x = (x_size / (max - min) / count_marker_x);
}

void drawer::calculate_scaling_log_y(const double& max, const double& min) {
    scaling_factor_y = (y_size / (max - min) / count_marker_y);
}

void drawer::set_linear_x() {
    linear_x = true;
}

void drawer::set_linear_y() {
    linear_y = true;
}

void drawer::set_log_x() {
    log_x = true;
}

void drawer::set_log_y() {
    log_y = true;
}