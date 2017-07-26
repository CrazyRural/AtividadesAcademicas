
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JRadioButton;


public class VendaTicketFunc {

	JFrame frame;
	public JRadioButton desjejum,alja;
	
	public VendaTicketFunc() {
		frame = new JFrame();
		frame.setBounds(550, 250, 300, 150);
		frame.setTitle("Vender Ticket");
		frame.setResizable(false);
		frame.getContentPane().setLayout(null);
		
		ButtonGroup preco = new ButtonGroup();
		
		desjejum = new JRadioButton("Pre\u00E7o Desjejum");
		desjejum.setBounds(6, 37, 133, 23);
		frame.getContentPane().add(desjejum);
		preco.add(desjejum);
		
		alja = new JRadioButton("Pre\u00E7o Almo\u00E7o/Jantar");
		alja.setBounds(6, 85, 133, 23);
		frame.getContentPane().add(alja);
		preco.add(alja);
		
		JButton btnVenderTicket = new JButton("Vender Ticket");
		btnVenderTicket.setBounds(172, 37, 112, 71);
		frame.getContentPane().add(btnVenderTicket);
		btnVenderTicket.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				venderClick();
			}
		});
		
	}
	private void venderClick(){
	float i;
	int j = TelaPrincipal.tabela1.getSelectedRow();
	
		if(desjejum.isSelected()){			
		i = TelaPrincipal.db.getFuncionario().get(j).getTicketsComprados() + (float) 3.0;	
		TelaPrincipal.db.getFuncionario().get(j).setTicketsComprados(i);
		TelaPrincipal.tabela1.preencheVazio();
		TelaPrincipal.tabela1.preenche();		
		}
		else{		
		i = TelaPrincipal.db.getFuncionario().get(j).getTicketsComprados() + (float) 6.0;
		TelaPrincipal.db.getFuncionario().get(j).setTicketsComprados(i);
		TelaPrincipal.tabela1.preencheVazio();
		TelaPrincipal.tabela1.preenche();	
		}			
		
		frame.dispose();
	}
}
