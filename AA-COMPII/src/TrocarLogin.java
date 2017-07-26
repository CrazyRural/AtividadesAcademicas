import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.BorderLayout;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;


public class TrocarLogin {

	JFrame frame;
	JTextField textField;
	JTextField textField_1;
	JTextField textField_2;
	JTextField textField_3;


	public TrocarLogin() {
		frame = new JFrame();
		frame.setBounds(400, 250, 450, 200);
		frame.setResizable(false);
		frame.setTitle("Trocar Login");
		JPanel panel = new JPanel();
		
		frame.getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(null);
		
		JLabel lblUsurioNovo = new JLabel("Usu\u00E1rio Novo:");
		lblUsurioNovo.setBounds(10, 50, 80, 14);
		panel.add(lblUsurioNovo);
		
		JLabel lblSenhaAtual = new JLabel("Senha Atual:");
		lblSenhaAtual.setBounds(10, 95, 80, 14);
		panel.add(lblSenhaAtual);
		
		JLabel lblNovaSenha = new JLabel("Nova Senha:");
		lblNovaSenha.setBounds(10, 136, 80, 14);
		panel.add(lblNovaSenha);
		
		JLabel lblUsurioAtual = new JLabel("Usu\u00E1rio Atual:");
		lblUsurioAtual.setBounds(10, 11, 80, 14);
		panel.add(lblUsurioAtual);
		
		textField = new JTextField();
		textField.setBounds(114, 11, 198, 20);
		panel.add(textField);
		textField.setColumns(10);
		
		textField_1 = new JTextField();
		textField_1.setColumns(10);
		textField_1.setBounds(114, 47, 198, 20);
		panel.add(textField_1);
		
		textField_2 = new JPasswordField();
		textField_2.setColumns(10);
		textField_2.setBounds(114, 92, 198, 20);
		panel.add(textField_2);
		
		textField_3 = new JPasswordField();
		textField_3.setColumns(10);
		textField_3.setBounds(114, 133, 198, 20);
		panel.add(textField_3);
		
		JButton btnNewButton = new JButton("SALVAR");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				salvarCLick();
			
				
			}
		});
		btnNewButton.setBounds(335, 50, 89, 59);
		panel.add(btnNewButton);
	}
	public void salvarCLick(){

		if(textField.getText().equals(Login.login) && textField_2.getText().equals(Login.senha)){
			Login.login = textField_1.getText();
			Login.senha = textField_3.getText();
			JOptionPane.showMessageDialog(frame, "Alterações Realizadas com Sucesso!", "Conclusão", JOptionPane.INFORMATION_MESSAGE);
			frame.dispose();
		}else{
			JOptionPane.showMessageDialog(frame, "Login/Senha Atuais Inválidos", "Aviso", JOptionPane.WARNING_MESSAGE);
		}

	}
}
