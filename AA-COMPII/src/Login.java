import java.awt.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import java.awt.event.*;

public class Login{
	JFrame frame;
	public static JTextField tfLogin;
	public static JPasswordField tfSenha;
	private JButton bLimpar, bLogar;
	private JLabel lUnidade1, lUnidade2;
	public static String login = "DEV";
	public static String senha = "intel";

	public Login(){
		
		//Nome Janela
		frame = new JFrame();
		frame.setTitle("Login");
		frame.setBounds(450,250,400,150);
		frame.setResizable(false);
		//Nome ao lado dos campos
		lUnidade1 = new JLabel ("Usu\u00E1rio:");
		lUnidade1.setBounds(25, 35, 50, 20);
		lUnidade2 = new JLabel ("Senha:");
		lUnidade2.setBounds(25, 85, 50, 20);
		frame.getContentPane().setLayout(null);
		frame.getContentPane().add(lUnidade1);
		frame.getContentPane().add(lUnidade2);
		//Campos para digitar	
		tfLogin = new JTextField();
		tfLogin.setBounds(120, 35, 100, 20);
		tfLogin.setToolTipText("Digite seu login aqui");
		tfLogin.setBackground(Color.lightGray);
		tfSenha = new JPasswordField();
		tfSenha.setBounds(120, 85, 100, 20);
		tfSenha.setToolTipText("Digite sua senha aqui (campo protegido)");
		tfSenha.setBackground(Color.lightGray);
		frame.getContentPane().add(tfLogin);
		frame.getContentPane().add(tfSenha);
		//Nome dos botoes e dicas		
		bLimpar = new JButton ("Limpar");
		bLimpar.setBounds(280, 75, 100, 40);
		bLimpar.setToolTipText("Limpe todos os campos de entrada");
		bLogar = new JButton ("Logar");
		bLogar.setBounds(280, 25, 100, 40);
		bLogar.setToolTipText("Efetue o login");
		frame.getContentPane().add(bLimpar);
		frame.getContentPane().add(bLogar);
		//Ao clicar em limpar e logar		
		bLimpar.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				bLimparClick();//metodo esta logo apos
			}
		});
		bLogar.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				bLogarClick();//metodo esta logo apos
			}
		});
	}
	
	//metodo para limpar o campo
	private void bLimparClick(){
		tfLogin.setText(""); 	tfSenha.setText("");
	}
	
	//metodo para login(inicial adm)
	@SuppressWarnings("deprecation")
	private void bLogarClick(){
		if(tfLogin.getText().equals(login) &&  tfSenha.getText().equals(senha)){
			TelaPrincipal p= new TelaPrincipal();
			p.frame.setVisible(true);
			frame.dispose();
		}
		else{
			Toolkit.getDefaultToolkit().beep();
			JOptionPane.showMessageDialog(frame, "Login ou Senha Inválidos", "Aviso", JOptionPane.WARNING_MESSAGE);
		}
	}
	
	
}
