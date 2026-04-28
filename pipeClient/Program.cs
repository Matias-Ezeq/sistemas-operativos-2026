using System.IO.Pipes;
class PipeClient
{
static void Main()
 {
using (var client = new NamedPipeClientStream(".", "mypipe",
PipeDirection.InOut))
 {
Console.WriteLine("Conectando al servidor...");
client.Connect();
Console.WriteLine("Conectado.");
using (var reader = new StreamReader(client))
using (var writer = new StreamWriter(client) { AutoFlush = true })
 {
writer.WriteLine("¡Hola servidor!");
string? response = reader.ReadLine();
Console.WriteLine("Respuesta del servidor: " + response);
 }
 }
 }
}