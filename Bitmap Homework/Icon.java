import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class Icon{

	private int rows;
	private int cols;
	private Pixel[][] pixels;

	//default constructor creates icon with 40x40 pixels
	public Icon(){						
		rows = 40;
		cols = 40;
		pixels = new Pixel[rows][cols];
		for(int i = 0; i< rows; i++){
			for(int j = 0; j < cols; j++){
				pixels[i][j] = new Pixel();
			}
		}
	}

	//custom constructor for XxY pixels
	public Icon(int x, int y){
		rows = x;
		cols = y;
		pixels = new Pixel[rows][cols];
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				pixels[i][j] = new Pixel();
			}
		}		
	}

	//gets the RGB values of a specific pixel
	public int getPixelRGB(int x, int y){
		int rgb = pixels[x][y].getRGB();
		int red = pixels[x][y].getRed();
		int green = pixels[x][y].getGreen();
		int blue = pixels[x][y].getBlue();
		System.out.println(rgb);
		System.out.println(red);
		System.out.println(green);
		System.out.println(blue);
		return rgb;
	}

	//sets the RGB value of a specific pixel using r,g,b
	public void setRGB(int x, int y, int r, int g, int b){
		pixels[x][y].setRed(r);
		pixels[x][y].setGreen(g);
		pixels[x][y].setBlue(b);
	}

	//prints pixel hex values to the screen
	public void printHexValues(){
		String[] hex_values = new String[cols];
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				hex_values[j] = pixels[i][j].getHex();
				System.out.print("  " + hex_values[j]);
			}

		}

	}

	//writes the pixels to a bitmap file for display
	public void saveBMP(String filename){

		try{			

			//creates the file
			File bmp_file = new File(filename);	
			//creates object to write bytes to the file
			FileOutputStream to_bmp_file = new FileOutputStream(bmp_file);

			//file size in bytes, needed as part of .bmp format
			int file_size = 54 + 3*rows*cols+ getPadding(cols)*rows;

			//BMP HEADER
			//general info about the file

			//creates an array of 2 bytes and puts the values 66,77 in the file (magic number for .bmp files)
			byte[] b = new byte[2];	
			b[0] = (byte) Integer.parseInt(Integer.toBinaryString(66),2);		
			b[1] = (byte) Integer.parseInt(Integer.toBinaryString(77),2);
			to_bmp_file.write(b);

			//creates 4 bytes with which the file size is stored
			b = new byte[4];
			b[0] = (byte) (file_size);
			b[1] = (byte) (file_size>>8);
			b[2] = (byte) (file_size>>16);
			b[3] = (byte) (file_size>>24);
			to_bmp_file.write(b);

			//the bytes between the previous array and b[4] of the next array are saved for specific applications
			//b[4] stores the range of bytes until pixel array info can be found
			b = new byte[8];
			b[4] = 54;
			to_bmp_file.write(b);

			//DIB HEADER
			//stores amount of bytes from here to end of DIB header
			b = new byte[4];
			b[0] = 40;
			to_bmp_file.write(b);

			//width of bitmap in pixels
			b = new byte[4];
			b[0] = (byte) cols;
			b[1] = (byte) (cols>>8);
			b[2] = (byte) (cols>>16);
			b[3] = (byte) (cols>>24);
			to_bmp_file.write(b);

			//height of bitmap in pixels
			b = new byte[4];
			b[0] = (byte) rows;
			b[1] = (byte) (rows>>8);
			b[2] = (byte) (rows>>16);
			b[3] = (byte) (rows>>24);
			to_bmp_file.write(b);

			//color planes being used
			b = new byte[2];
			b[0] = 1;
			to_bmp_file.write(b);

			//bits per pixel
			b = new byte[2];
			b[0] = 24;
			to_bmp_file.write(b);

			//bi_RGB
			b = new byte[4];
			to_bmp_file.write(b);

			//size of raw data in pixel array including padding
			b = new byte[4];
			b[0] = 16;
			to_bmp_file.write(b);

			//horizontal resolution
			b = new byte[4];
			b[0] = (byte) Integer.parseInt(Integer.toBinaryString(2835),2);		
			to_bmp_file.write(b);
			
			//vertical resolution
			b = new byte[4];
			b[0] = (byte) Integer.parseInt(Integer.toBinaryString(2835),2);
			to_bmp_file.write(b);

			//number of colors in image
			b = new byte[4];
			to_bmp_file.write(b);

			// number of important colors
			b = new byte[4];
			to_bmp_file.write(b);

			//PIXEL ARRAY		
			//goes through pixels in Icon and writes their rgb value to the file	
			for(int i = 0; i < rows; i++){
				for(int j = 0; j < cols; j++){					
					b = new byte[3];					
					b[0] = (byte) pixels[i][j].getRed();
					b[1] = (byte) pixels[i][j].getGreen();
					b[2] = (byte) pixels[i][j].getBlue();
					to_bmp_file.write(b);
				}
				//this is here so every row ends as a multiple of 4
				for(int j = 0; j < getPadding(cols); j++){
					b = new byte[1];
					to_bmp_file.write(b);
				}
			}
		} 
		catch (FileNotFoundException e) {			
		} 
		catch (IOException e) {			
		}
	}
	//used to make sure every row ends as a multiple of 4
	private int getPadding(int row){		
		int padding = ( 3* row) % 4;
		if(padding != 0)
			padding = 4 - padding;		
		return padding;
	}
}
	