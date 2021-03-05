class ConnectionFabric {
public:
	static socket* open_connection(); //Создает объект типа socket и возвращает указатель на него

	static socket* clone_connection(socket* ptr); //Копирует уже существующий объект типа socket и возвращает указатель на копию

	static void close_connection(socket* ptr); //Удаляет объект типа socket по его адресу. 
};

class connection_storage {
public:
	connection_storage() : target(nullptr) {} // конструктор по умолчанию ничего не делает

	connection_storage(connection_storage const& rhs); //конструктор копирования
	connection_storage(connection_storage&& rhs); //конструктор перемещения

	socket* connection(); //возвращает указатель на socket
	socket const* connection() const; //аналогично выше, но с const 
private:
	const socket* target;
};

connection_storage::connection_storage(connection_storage const& rhs) : target(ConnectionFabric::clone_connection(rhs.connection()))
{

}

connection_storage::connection_storage(connection_storage&& rhs) : target(rhs.connection())
{
	ConnectionFabric::close_connection(rhs.connection());
	rhs.~connection_storage();
}

socket* connection_storage::connection()
{
	return const_cast<socket*>(target);
}

socket const* connection_storage::connection() const
{
	return target;
}
