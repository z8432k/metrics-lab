#include "reg.h"
#include <algorithm>

reg::reg() : in(DATA), out(DATE) {
    if (!in.is_open() | !out.is_open()) {
        cerr << "Файл не может быть открыт." << endl;
    }

    while (getline(in, buf)) {
        tickets.push_back(buf);
    }

    setDate();

    in.close();
}

void reg::showTickets(vector<string> *r) {
    size_t cnt = 1;

    if (r==nullptr) {
        r = &tickets;
    }

    for (auto &item :  *r) {
        cout << cnt++ << "\t" << item << endl;
    }
}


void reg::show() {
    if (down) {
        downsort();
    }
    else {
        upsort();
    }
}

void reg::emptyBase() {
    tickets.clear();

    function<void (ofstream &out)> cb = [](ofstream &outD) -> void {
        outD << "";
    };

    aroundData(cb);
}

bool reg::addTicket() {
    string ticket = inputTicket();

    function<void (ofstream &out)> cb = [this, &ticket](ofstream &outD) -> void {
        tickets.push_back(ticket);
    };

    aroundData(cb);

    return true;
}

string reg::inputTicket() {
    string ticket;
    int number = findmax() + 1;
    string fio;
    int window;

    cout << "Введите ФИО" << endl;
    fio = str();

    cout << "Введите номер окна" << endl;
    window = num(0, 5);

    ticket = to_string(number) + "\t" + fio + "\t" + to_string(window);

    return ticket;
}

int reg::num(size_t min, size_t max) {
    int res;

    while (true) {
        cin >> res;

        if (res > min && res <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            return res;
        } else {
            cerr << "Ошибка. Попробуйте ещё раз." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void reg::setDate() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    out << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour << ":"
        << ltm->tm_min << ":" << ltm->tm_sec << endl;

    out.close();
}

string reg::str() {
    while (true) {
        string str;
        getline(cin, str);

        if (str.length() >= 2) {
            return str;
        } else {
            cerr << "Слишком короткий текст." << endl;
        }
    }
}

void reg::updateTicket(int id) {
    string t = inputTicket();

    function<void (ofstream &out)> cb = [this, &id, &t](ofstream &outD) -> void {
        if (tickets.size() > id) {
            tickets.at(id - 1) = t;
        } else {
            cerr << "Номер в очереди не найден" << endl;
        }
    };

    aroundData(cb);
}

bool reg::drop(int id) {
    bool flag = true;


    function<void (ofstream &out)> cb = [this, &id, &flag](ofstream &outD) -> void {
        if (tickets.size() > id) {
            tickets.erase(tickets.begin() + (id - 1));
        } else {
            cerr << "Номер в очереди не найден." << endl;
            flag = false;
        }
    };

    aroundData(cb);

    return flag;
}

void reg::upsort() {
    vector<string> sorted = tickets;
    sort(sorted.begin(), sorted.end());

    showTickets(&sorted);
}

void reg::downsort() {
    vector<string> sorted = tickets;
    sort(sorted.begin(), sorted.end(), greater<>());

    showTickets(&sorted);
}

void reg::aroundData(function<void(ofstream &)> &callback) {
    outData.open(DATA);

    if (!outData.is_open()) {
        cerr << "Ошибка открытия файла данных.";
    }

    callback(outData);

    for (auto &item : tickets) {
        outData << item << endl;
    }

    outData.close();
}

void reg::changeSortOrder() {
    down = !down;
}

string reg::searchTicket(int id) {
    string result;
    string sid = to_string(id);

    auto found = find_if(tickets.begin(), tickets.end(), [&sid](string &item) {
        vector<string> items;
        split(item, items, '\t');

        if (items[0] == sid) {
            return true;
        }

        return false;
    });

    return found[0];
}


size_t reg::split(const std::string &str, std::vector<std::string> &items, char sep) {
    size_t pos = str.find(sep);
    size_t initialPos = 0;
    items.clear();

    while(pos != std::string::npos) {
        items.push_back(str.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = str.find(sep, initialPos );
    }

    items.push_back(str.substr( initialPos, std::min( pos, str.size() ) - initialPos + 1));

    return items.size();
}

int reg::findmax() {
    int max = 1;
    vector<string> items;
    int cur;

    for (auto &t : tickets) {
        auto cnt = split(t, items, '\t');

        if (cnt > 0) {
            cur = stoi(items[0]);

            if (cur > max) {
                max = cur;
            }
        }
    }

    return max;
}
