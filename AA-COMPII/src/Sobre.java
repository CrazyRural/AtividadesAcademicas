import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JLabel;

import java.awt.BorderLayout;

import javax.swing.JTextPane;

import java.awt.Color;
import java.awt.Desktop;
import java.awt.Font;
import java.awt.TextArea;
import java.awt.Label;

import javax.swing.JEditorPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.ImageIcon;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.net.URL;


public class Sobre {

	JFrame frame;

	
	public Sobre() {

		frame = new JFrame();
		frame.setBounds(450, 200, 450, 300);
		frame.setBackground(Color.BLACK);
		frame.setTitle("Sobre");
		frame.getContentPane().setLayout(null);
		frame.setResizable(false);
		
		JLabel lblPorJoo = new JLabel("                                    Por : Jo\u00E3o Victor Ara\u00FAjo e Reinaldo Moraes ");
		lblPorJoo.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblPorJoo.setBounds(0, 26, 434, 35);
		frame.getContentPane().add(lblPorJoo);
		
		JLabel lblNewLabel = new JLabel("   Controle do R.U. (v 1.0b) desenvolvido na UFRRJ");
		lblNewLabel.setBounds(0, 0, 434, 22);
		frame.getContentPane().add(lblNewLabel);
		lblNewLabel.setFont(new Font("Tahoma", Font.PLAIN, 18));
		
		Label label = new Label("                                   "
				+ " Curta no Facebook!");
		label.setBounds(0, 55, 434, 69);
		frame.getContentPane().add(label);
		label.setFont(new Font("Arial", Font.BOLD | Font.ITALIC, 15));
		
		JButton btnGo = new JButton();
		btnGo.setBounds(155, 125, 128, 128);
		btnGo.setIcon(new ImageIcon("C:\\Users\\Joao Victor Araujo\\Desktop\\Icons\\Icon4.png"));
		btnGo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				try 
		        {
		            Desktop.getDesktop().browse(new URL("https://www.facebook.com/direcao.im").toURI());
		        }           
		        catch (Exception e) {
		        	JOptionPane.showMessageDialog(frame, "Navegador não encontrado", "Aviso", JOptionPane.WARNING_MESSAGE);
		        }
			}
		});
		frame.getContentPane().add(btnGo);
	}
}
