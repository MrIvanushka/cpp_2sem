class connection_storage {
public:
	connection_storage() : target(ConnectionFabric::open_connection()) {} // конструктор по умолчанию ничего не делает
        ~connection_storage()
        {
            if (target != nullptr)
            {
                ConnectionFabric::close_connection(target);
            }
             target = nullptr;
        }
	connection_storage(connection_storage const& rhs); //конструктор копирования
	connection_storage(connection_storage&& rhs); //конструктор перемещения

	socket* connection(); //возвращает указатель на socket
	socket const* connection() const; //аналогично выше, но с const 
private:
	socket* target;
};

connection_storage::connection_storage(connection_storage const& rhs) : target(ConnectionFabric::clone_connection(const_cast<socket*>(rhs.connection())))
{

}

connection_storage::connection_storage(connection_storage&& rhs) : target(rhs.connection())
{
	//ConnectionFabric::close_connection(rhs.connection());
	//rhs.target = nullptr;
}

socket* connection_storage::connection()
{
	return target;
}

socket const* connection_storage::connection() const
{
        const socket* CT = target;
	return CT;
}
