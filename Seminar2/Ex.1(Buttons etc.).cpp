//Вам дан следующий набор абстрактных классов для описания элементов графического интерфейса.
enum class control_type {
  button,
  check_box,
  text_box
};

class control_i {
public:
  explicit control_i(control_type type) : type_{type} {}

  virtual void action() = 0; //выполнить какое-то действие

  virtual void reset() = 0; //сбросить своё состояние

  control_type const &type() const { return type_; } // возвращает тип элемента

  virtual ~control_i() = default;

private:
  control_type type_;
};

class widget_i {
public:
  explicit widget_i(std::string name) : name_{std::move(name)} {}

  virtual void draw() const = 0; //нарисовать элемент

  std::string const &name() const { return name_; } //возвращает имя элемента

  virtual ~widget_i() = default;

private:
  std::string name_;
};
//Вам необходимо реализовать следующие классы, унаследованные от вышеописанных:

class button : public control_i, public widget_i {
public:
	explicit button(std::string name) : control_i(control_type::button), widget_i(name), Clicked(false) {} //конструктор принимает имя объекта

	void draw() const override;

	void action() override;

	void reset() override;

	bool clicked(); //возвращает true, если кнопка нажата и false, если нет
private:
		void DrawButton(std::string const& name, char Corner) const;
		bool Clicked;
};

bool button::clicked()
{
	return Clicked;
}
void button::draw() const
{
	if (Clicked)
		DrawButton(this->name(), '+');
	else
		DrawButton(this->name(), '*');
}
void button::DrawButton(std::string const& name, char Corner) const
{
	unsigned&& Len = name.length() + 2;
	for (unsigned i = 0; i < Len; i++)
		std::cout << Corner;
	std::cout << '\n';

	std::cout << Corner << name << Corner;
	std::cout << '\n';

	for (unsigned i = 0; i < Len; i++)
		std::cout << Corner;
	std::cout << '\n';
}
void button::action()
{
	Clicked = true;
}
void button::reset()
{
	Clicked = false;
}

class troll_button : public button
{
public:
	troll_button(std::string name) : button(name), Visible(true) {}

	void action() override;

	void draw() const override;

	void make_visible();
private:
	bool Visible;
};

void troll_button::action()
{
	button::action();
	Visible = false;
}
void troll_button::make_visible()
{
	Visible = true;
}
void troll_button::draw() const
{
	if (Visible)
		button::draw();
}

class check_box : public control_i, public widget_i {
public:
	explicit check_box(std::string name) : control_i(control_type::check_box), widget_i(name), Checked(false) {} //имя объекта

	void draw() const override;

	void action() override;
	void reset() override {}

	bool checked(); //true если объект выбран, false если нет. (изначально состояние объекта должно быть false)
private:
	bool Checked;
};

bool check_box::checked()
{
	return Checked;
}
void check_box::draw() const
{
	std::cout << "***" << '\n' << "*";
	
	if (Checked)
		std::cout << '#';
	else
		std::cout << ' ';

	std::cout << "*" << '\n' << "***" << '\n';
}
void check_box::action()
{
	Checked = !Checked;
}

class text_box : public control_i, public widget_i {
public:
	text_box(std::string text, std::string name) : control_i(control_type::text_box), widget_i(name), Text(text) {} //текст и имя объекта
	
	void draw() const override;
	void action() override {}
	void reset() override {}
private:
	std::string Text;
};

void text_box::draw() const
{
	unsigned&& Len = Text.length();

	std::cout << '*';
	for (unsigned i = 0; i < Len; i++)
		std::cout << '-';

	std::cout << '*' << '\n' << '|' << Text << '|' << '\n';

	std::cout << '*';
	for (unsigned i = 0; i < Len; i++)
		std::cout << '-';
	std::cout << '*' << '\n';
}
