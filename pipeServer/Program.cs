using System.IO.Pipes;
class PipeServer
{
static void Main()
 {
using (var server = new NamedPipeServerStream("mypipe"))
 {
 Console.WriteLine("Esperando conexión del cliente...");
server.WaitForConnection();
 Console.WriteLine("Cliente conectado.");
using (var reader = new StreamReader(server))
using (var writer = new StreamWriter(server) {
 AutoFlush = true })
 {
string? message = reader.ReadLine();
 Console.WriteLine("Mensaje recibido: " + message);
writer.WriteLine("Hola cliente, recibí tu mensaje: " +
 message);
 }
 }
 }
}