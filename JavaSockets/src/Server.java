import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;


public class Server {
	private static final int PORT= 4444;


	public static void main(String[] args){
		System.out.println("Server started!");
		//Initialize socket and streams
		Socket socket = null;
		ObjectOutputStream outputStream = null;
		ObjectInputStream inputStream = null;

		try {
			//Create new server socket
			ServerSocket server = new ServerSocket(PORT);

			System.out.println("Server created, waiting for socket...");

			socket = server.accept();

			System.out.println("Socket connected!");

			OutputStream outputS = socket.getOutputStream();
			outputStream = new ObjectOutputStream(outputS);
			outputStream.flush();

			InputStream inputS = socket.getInputStream();
			inputStream =		new ObjectInputStream(inputS);

				System.out.println("Waiting for message...");
				int arraySize = inputStream.readInt();
		
				
				Integer sum = 0;
				for (int i=0; i<arraySize; i++){
				Integer num = inputStream.readInt();
				sum += num; 
				}
				outputStream.writeInt(sum);
				outputStream.flush();
			}
		catch (IOException e) {
			e.printStackTrace();
		}
		finally {
			System.out.println("cleaning up...");

			// Exception or not, clean up the streams and socket.
			try {
				
					outputStream.close();
				

				
					inputStream.close();
				

				
					socket.close();
				
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}

	}










}


