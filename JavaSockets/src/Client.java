import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Scanner;

public class Client {
	private static final int PORT = 4444;

	public Client() {
		ObjectOutputStream outputStream = null;
		ObjectInputStream inputStream = null;
		ArrayList<Integer> clientArray = getClientArray();
		Socket socket = null;
		
		System.out.println("Client started!");

		try {
			System.out.println("Creating socket...");
			
			socket = new Socket(InetAddress.getLocalHost(), PORT);
			
			System.out.println("Socket connected!!!");

			OutputStream outputS = socket.getOutputStream();
			outputStream = new ObjectOutputStream(outputS);
			outputStream.flush();

			InputStream inputS = socket.getInputStream();
			inputStream = new ObjectInputStream(inputS);

			try {
				System.out.println("sending: " + clientArray.size());
				outputStream.writeInt(clientArray.size());
				outputStream.flush();
				
				System.out.println("sending: " + clientArray);
				for (Integer i: clientArray){
					outputStream.writeInt(i);
					outputStream.flush();
				}
				
				Integer arraySum = inputStream.readInt();
				System.out.println("recieving: " + arraySum);
				
				
			} catch (IOException ex) {
				ex.printStackTrace();
			}



			
		} catch (IOException e) {
			e.printStackTrace();
		}

		finally {
			System.out.println("cleaning up...");

			// Exception or not, clean up the streams and socket.
			
					try {
						inputStream.close();
						
						socket.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
				
			} 
		}

	

	private static ArrayList<Integer> getClientArray() {
		ArrayList<Integer> intArray = new ArrayList<Integer>();
		Scanner input = new Scanner(System.in);
		String clientInput;

		System.out.println("Enter Int:");

		for (clientInput = input.nextLine(); clientInput != null; clientInput = input
				.nextLine()) {
			if (clientInput.isEmpty()) {
				break;
			}
			intArray.add(Integer.parseInt(clientInput));
			System.out.println("Enter Int:");

		}
		return intArray;

	}
	public static void main(String[] args){
		new Client();
	}
}
