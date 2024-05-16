<template>
	<view >
		<view class="pay-area">
			<image class="pay-img" src = "../../static/pay.png" mode = "widthFix"></image>
		</view>	
		
		<view class="btn-area">
			<button class="btn-pay" @tap="backToMenu"> 返回 </button>
		</view> 
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			backToMenu(){
				uni.navigateTo({
					url:'./index'
				})
			}
		}
	}
</script>

<style>
	.pay-img{
		display: block;
		margin: 0 auto;
	}
	.btn-pay{
		margin-top: 35rpx;
		font-size: 50rpx;
		height: 60px;
		margin-left: 20px;
		margin-right: 20px;
		background-color: #48d75a;
		border-radius: 30rpx;
	}
</style>
