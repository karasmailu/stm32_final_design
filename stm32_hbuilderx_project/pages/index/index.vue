<template>
	<view class = "warp">
		<view class = "sys-state-tip">
			设备状态
		</view>
		<view class="dev-area">
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>小时</view>
					<image class="dev-logo" src = "../../static/hour.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_Hour}}H</view>
			</view>
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>分钟</view>
					<image class="dev-logo" src = "../../static/min.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_Min}}M</view>
			</view>
		</view>
		<view class="dev-area">			
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>电压</view>
					<image class="dev-logo" src = "../../static/U.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_U}}V</view>
			</view>
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>电流</view>
					<image class="dev-logo" src = "../../static/A.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_A}}A</view>
			</view>
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>功率</view>
					<image class="dev-logo" src = "../../static/W.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_W}}W</view>
			</view>
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>电量</view>
					<image class="dev-logo" src = "../../static/charge.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_Charge}}kWh</view>
			</view>	
			
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>供电开关</view>
					<image class="dev-logo" src = "../../static/switch.png" mode = ""></image>
				</view>
				<switch :checked="dev_Stat" @change="CrtlOneNetDev" color="#2b9939"></switch>
			</view>
			<view class="dev-card">
				<view class = "">
					<view class = 'dev-name'>花费</view>
					<image class="dev-logo" src = "../../static/money.png" mode = ""></image>
				</view>
				<view class = "dev-data">{{dev_Money}}元</view>
			</view>	
	</view>
		
		<view>
		   <view class="btn-area">
			   <button class="btn-pay" @tap="goToPay">支付 {{dev_Money}}元</button>
		   </view> 
		</view>
	</view>	

</template>

<script>
	const {//从外部装载生成token密钥的函数
		createCommonToken
	} = require('@/key.js')
	export default {
		data() {
			return {
				//定义需要显示的信息
				dev_Hour:'',
				dev_Money: '',
				dev_Min:'',
				dev_U: '',//设备上传到云平台的电压
				dev_A: '',//设备上传到云平台的电流
				dev_W: '',//设备上传到云平台的电功率（计算）
				dev_Charge:'',
				dev_Stat: false,//继电器状态
				token: '',//生成的token密钥
			}
		},
		onLoad() {
			const params = {
				author_key: 'kcLCByS36KBgtV9lBg0/Rx7yGyhfcwWa6DbCFzk9vw9WubEbe17P8dfWnHll977uZO1cG1fMFEWTCllJVLwU7A==',
				version: '2022-05-01',
				user_id: '326108',
			}
			//生成token密钥
			this.token = createCommonToken(params);
			
		},
		
		//显示云平台数据
		onShow(){
			this.getOneNetData();
			//定时3秒获取一次
			setInterval(()=>{
				this.getOneNetData();
			},3000)
		},
		
		
		methods: {
			//跳转支付页面
			goToPay(){
				uni.navigateTo({
					url:'./pay'
				})
			},
			//获取onenet云平台的数据
			getOneNetData(){
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/query-device-property', //onenet云平台接口地址
					method:'GET',
					//设备ID和名称
					data: {
						product_id:'Lu7Lu5L6qP',
						device_name:'test'
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: (res) => {
						console.log(res.data);
						console.log(res.data.data[0].value);
						
						//显示信息
						//需要自己在云平台或者终端上面确定顺序
						this.dev_A = res.data.data[0].value;
						this.dev_Charge = res.data.data[1].value;
						this.dev_Hour = res.data.data[2].value;
						this.dev_Min = res.data.data[3].value;
						this.dev_Stat = res.data.data[4].value === 'true' ? true:false;
						this.dev_U = res.data.data[5].value;
						this.dev_W = ((this.dev_U*1) * (this.dev_A*1)).toFixed(2);//计算电功率,2位小数
						this.dev_Money = this.dev_Hour*1 + this.dev_Min*0.01;//根据时间计算金额
					}
				})				
			},
			CrtlOneNetDev(event){
				console.log(event.detail.value);
				let val = event.detail.value;
				uni.request({
					url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', //onenet云平台接口地址
					method:'POST',
					//设备ID和名称
					data: {
						product_id:'Lu7Lu5L6qP',
						device_name:'test',
						params:{ "dev_State":val}
					},
					header: {
						'authorization': this.token //自定义请求头信息
					},
					success: (res) => {
						console.log();
					}
				})				
			}

		}
	}
</script>

<style>
	.warp{
		padding: 20rpx;
	}
	//类属性的设置
	.dev-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}
	.dev-card {
		height: 150rpx;
		width: 330rpx;
		border-radius: 30rpx;
		display: flex;
		margin-top: 35rpx;
		justify-content: space-around;
		align-items: center;
		box-shadow: 0 0 15rpx #ccc;
	}

	.dev-logo {
		width: 70rpx;
		height: 70rpx;
		margin-top: 10rpx; 
	}
	.dev-name{
		font-size: 35rpx;
		text-align: center;
		color: #6d6d6d;
	}
	.dev-data { 
		font-size: 50rpx;
		color: #6d6d6d;		
	}
	.sys-state-tip{
		height: 100rpx;
		width: 710rpx;
		font-size: 50rpx;
		border-radius: 30rpx;
		display: flex;
		margin-top: 35rpx;
		justify-content: space-around;
		align-items: center;
		color: #36b246;
		box-shadow: 0 0 15rpx #ccc;	
	}
	
	.title {
		font-size: 36rpx;
		color: #48d75a;
	}
	.btn-pay{
		margin-top: 35rpx;
		margin-left: 30rpx;
		margin-right: 30rpx;
		font-size: 50rpx;
		border-radius: 30rpx;
		background-color: #48d75a;
	}

</style>