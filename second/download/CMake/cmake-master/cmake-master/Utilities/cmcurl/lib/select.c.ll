; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/select.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timeval = type { i64, i64 }
%struct.pollfd = type { i32, i16, i16 }

@Curl_ack_eintr = global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @Curl_wait_ms(i32 %timeout_ms) #0 !dbg !6 {
entry:
  %retval = alloca i32, align 4
  %timeout_ms.addr = alloca i32, align 4
  %initial_tv = alloca %struct.timeval, align 8
  %pending_ms = alloca i32, align 4
  %error = alloca i32, align 4
  %r = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  %agg.tmp = alloca %struct.timeval, align 8
  store i32 %timeout_ms, i32* %timeout_ms.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timeout_ms.addr, metadata !36, metadata !37), !dbg !38
  call void @llvm.dbg.declare(metadata %struct.timeval* %initial_tv, metadata !39, metadata !37), !dbg !46
  call void @llvm.dbg.declare(metadata i32* %pending_ms, metadata !47, metadata !37), !dbg !48
  call void @llvm.dbg.declare(metadata i32* %error, metadata !49, metadata !37), !dbg !50
  call void @llvm.dbg.declare(metadata i32* %r, metadata !51, metadata !37), !dbg !52
  store i32 0, i32* %r, align 4, !dbg !52
  %0 = load i32, i32* %timeout_ms.addr, align 4, !dbg !53
  %tobool = icmp ne i32 %0, 0, !dbg !53
  br i1 %tobool, label %if.end, label %if.then, !dbg !55

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !56
  br label %return, !dbg !56

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %timeout_ms.addr, align 4, !dbg !57
  %cmp = icmp slt i32 %1, 0, !dbg !59
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !60

if.then1:                                         ; preds = %if.end
  %call = call i32* @__errno_location() #1, !dbg !61
  store i32 22, i32* %call, align 4, !dbg !61
  store i32 -1, i32* %retval, align 4, !dbg !63
  br label %return, !dbg !63

if.end2:                                          ; preds = %if.end
  %2 = load i32, i32* %timeout_ms.addr, align 4, !dbg !64
  store i32 %2, i32* %pending_ms, align 4, !dbg !65
  %call3 = call { i64, i64 } @curlx_tvnow(), !dbg !66
  %3 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !66
  %4 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 0, !dbg !66
  %5 = extractvalue { i64, i64 } %call3, 0, !dbg !66
  store i64 %5, i64* %4, align 8, !dbg !66
  %6 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 1, !dbg !66
  %7 = extractvalue { i64, i64 } %call3, 1, !dbg !66
  store i64 %7, i64* %6, align 8, !dbg !66
  %8 = bitcast %struct.timeval* %initial_tv to i8*, !dbg !66
  %9 = bitcast %struct.timeval* %coerce to i8*, !dbg !66
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* %9, i64 16, i32 8, i1 false), !dbg !67
  br label %do.body, !dbg !69

do.body:                                          ; preds = %do.cond, %if.end2
  %10 = load i32, i32* %pending_ms, align 4, !dbg !70
  %call4 = call i32 @poll(%struct.pollfd* null, i64 0, i32 %10), !dbg !72
  store i32 %call4, i32* %r, align 4, !dbg !73
  %11 = load i32, i32* %r, align 4, !dbg !74
  %cmp5 = icmp ne i32 %11, -1, !dbg !76
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !77

if.then6:                                         ; preds = %do.body
  br label %do.end, !dbg !78

if.end7:                                          ; preds = %do.body
  %call8 = call i32* @__errno_location() #1, !dbg !79
  %12 = load i32, i32* %call8, align 4, !dbg !79
  store i32 %12, i32* %error, align 4, !dbg !80
  %13 = load i32, i32* %error, align 4, !dbg !81
  %tobool9 = icmp ne i32 %13, 0, !dbg !81
  br i1 %tobool9, label %land.lhs.true, label %if.end13, !dbg !83

land.lhs.true:                                    ; preds = %if.end7
  %14 = load i32, i32* @Curl_ack_eintr, align 4, !dbg !84
  %tobool10 = icmp ne i32 %14, 0, !dbg !84
  br i1 %tobool10, label %if.then12, label %lor.lhs.false, !dbg !84

lor.lhs.false:                                    ; preds = %land.lhs.true
  %15 = load i32, i32* %error, align 4, !dbg !86
  %cmp11 = icmp ne i32 %15, 4, !dbg !86
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !88

if.then12:                                        ; preds = %lor.lhs.false, %land.lhs.true
  br label %do.end, !dbg !89

if.end13:                                         ; preds = %lor.lhs.false, %if.end7
  %16 = load i32, i32* %timeout_ms.addr, align 4, !dbg !90
  %call14 = call { i64, i64 } @curlx_tvnow(), !dbg !91
  %17 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !91
  %18 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %17, i32 0, i32 0, !dbg !91
  %19 = extractvalue { i64, i64 } %call14, 0, !dbg !91
  store i64 %19, i64* %18, align 8, !dbg !91
  %20 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %17, i32 0, i32 1, !dbg !91
  %21 = extractvalue { i64, i64 } %call14, 1, !dbg !91
  store i64 %21, i64* %20, align 8, !dbg !91
  %22 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !91
  %23 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %22, i32 0, i32 0, !dbg !91
  %24 = load i64, i64* %23, align 8, !dbg !91
  %25 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %22, i32 0, i32 1, !dbg !91
  %26 = load i64, i64* %25, align 8, !dbg !91
  %27 = bitcast %struct.timeval* %initial_tv to { i64, i64 }*, !dbg !91
  %28 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %27, i32 0, i32 0, !dbg !91
  %29 = load i64, i64* %28, align 8, !dbg !91
  %30 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %27, i32 0, i32 1, !dbg !91
  %31 = load i64, i64* %30, align 8, !dbg !91
  %call15 = call i64 @curlx_tvdiff(i64 %24, i64 %26, i64 %29, i64 %31), !dbg !92
  %conv = trunc i64 %call15 to i32, !dbg !91
  %sub = sub nsw i32 %16, %conv, !dbg !94
  store i32 %sub, i32* %pending_ms, align 4, !dbg !95
  %32 = load i32, i32* %pending_ms, align 4, !dbg !96
  %cmp16 = icmp sle i32 %32, 0, !dbg !98
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !99

if.then18:                                        ; preds = %if.end13
  store i32 0, i32* %r, align 4, !dbg !100
  br label %do.end, !dbg !102

if.end19:                                         ; preds = %if.end13
  br label %do.cond, !dbg !103

do.cond:                                          ; preds = %if.end19
  %33 = load i32, i32* %r, align 4, !dbg !104
  %cmp20 = icmp eq i32 %33, -1, !dbg !105
  br i1 %cmp20, label %do.body, label %do.end, !dbg !106

do.end:                                           ; preds = %do.cond, %if.then18, %if.then12, %if.then6
  %34 = load i32, i32* %r, align 4, !dbg !107
  %tobool22 = icmp ne i32 %34, 0, !dbg !107
  br i1 %tobool22, label %if.then23, label %if.end24, !dbg !109

if.then23:                                        ; preds = %do.end
  store i32 -1, i32* %r, align 4, !dbg !110
  br label %if.end24, !dbg !111

if.end24:                                         ; preds = %if.then23, %do.end
  %35 = load i32, i32* %r, align 4, !dbg !112
  store i32 %35, i32* %retval, align 4, !dbg !113
  br label %return, !dbg !113

return:                                           ; preds = %if.end24, %if.then1, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !114
  ret i32 %36, !dbg !114
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #2

declare { i64, i64 } @curlx_tvnow() #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @poll(%struct.pollfd*, i64, i32) #3

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #3

; Function Attrs: nounwind uwtable
define i32 @Curl_socket_check(i32 %readfd0, i32 %readfd1, i32 %writefd, i64 %timeout_ms) #0 !dbg !9 {
entry:
  %retval = alloca i32, align 4
  %readfd0.addr = alloca i32, align 4
  %readfd1.addr = alloca i32, align 4
  %writefd.addr = alloca i32, align 4
  %timeout_ms.addr = alloca i64, align 8
  %pfd = alloca [3 x %struct.pollfd], align 16
  %num = alloca i32, align 4
  %initial_tv = alloca %struct.timeval, align 8
  %pending_ms = alloca i32, align 4
  %error = alloca i32, align 4
  %r = alloca i32, align 4
  %ret = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  %agg.tmp = alloca %struct.timeval, align 8
  store i32 %readfd0, i32* %readfd0.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %readfd0.addr, metadata !115, metadata !37), !dbg !116
  store i32 %readfd1, i32* %readfd1.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %readfd1.addr, metadata !117, metadata !37), !dbg !118
  store i32 %writefd, i32* %writefd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %writefd.addr, metadata !119, metadata !37), !dbg !120
  store i64 %timeout_ms, i64* %timeout_ms.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %timeout_ms.addr, metadata !121, metadata !37), !dbg !122
  call void @llvm.dbg.declare(metadata [3 x %struct.pollfd]* %pfd, metadata !123, metadata !37), !dbg !127
  call void @llvm.dbg.declare(metadata i32* %num, metadata !128, metadata !37), !dbg !129
  call void @llvm.dbg.declare(metadata %struct.timeval* %initial_tv, metadata !130, metadata !37), !dbg !131
  %0 = bitcast %struct.timeval* %initial_tv to i8*, !dbg !131
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 16, i32 8, i1 false), !dbg !131
  call void @llvm.dbg.declare(metadata i32* %pending_ms, metadata !132, metadata !37), !dbg !133
  store i32 0, i32* %pending_ms, align 4, !dbg !133
  call void @llvm.dbg.declare(metadata i32* %error, metadata !134, metadata !37), !dbg !135
  call void @llvm.dbg.declare(metadata i32* %r, metadata !136, metadata !37), !dbg !137
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !138, metadata !37), !dbg !139
  %1 = load i64, i64* %timeout_ms.addr, align 8, !dbg !140
  %cmp = icmp sge i64 %1, 2147483647, !dbg !142
  br i1 %cmp, label %if.then, label %if.end, !dbg !143

if.then:                                          ; preds = %entry
  store i64 2147483647, i64* %timeout_ms.addr, align 8, !dbg !144
  br label %if.end, !dbg !145

if.end:                                           ; preds = %if.then, %entry
  %2 = load i32, i32* %readfd0.addr, align 4, !dbg !146
  %cmp1 = icmp eq i32 %2, -1, !dbg !148
  br i1 %cmp1, label %land.lhs.true, label %if.end6, !dbg !149

land.lhs.true:                                    ; preds = %if.end
  %3 = load i32, i32* %readfd1.addr, align 4, !dbg !150
  %cmp2 = icmp eq i32 %3, -1, !dbg !152
  br i1 %cmp2, label %land.lhs.true3, label %if.end6, !dbg !153

land.lhs.true3:                                   ; preds = %land.lhs.true
  %4 = load i32, i32* %writefd.addr, align 4, !dbg !154
  %cmp4 = icmp eq i32 %4, -1, !dbg !155
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !156

if.then5:                                         ; preds = %land.lhs.true3
  %5 = load i64, i64* %timeout_ms.addr, align 8, !dbg !158
  %conv = trunc i64 %5 to i32, !dbg !160
  %call = call i32 @Curl_wait_ms(i32 %conv), !dbg !161
  store i32 %call, i32* %r, align 4, !dbg !162
  %6 = load i32, i32* %r, align 4, !dbg !163
  store i32 %6, i32* %retval, align 4, !dbg !164
  br label %return, !dbg !164

if.end6:                                          ; preds = %land.lhs.true3, %land.lhs.true, %if.end
  %7 = load i64, i64* %timeout_ms.addr, align 8, !dbg !165
  %cmp7 = icmp sgt i64 %7, 0, !dbg !167
  br i1 %cmp7, label %if.then9, label %if.end12, !dbg !168

if.then9:                                         ; preds = %if.end6
  %8 = load i64, i64* %timeout_ms.addr, align 8, !dbg !169
  %conv10 = trunc i64 %8 to i32, !dbg !171
  store i32 %conv10, i32* %pending_ms, align 4, !dbg !172
  %call11 = call { i64, i64 } @curlx_tvnow(), !dbg !173
  %9 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !173
  %10 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %9, i32 0, i32 0, !dbg !173
  %11 = extractvalue { i64, i64 } %call11, 0, !dbg !173
  store i64 %11, i64* %10, align 8, !dbg !173
  %12 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %9, i32 0, i32 1, !dbg !173
  %13 = extractvalue { i64, i64 } %call11, 1, !dbg !173
  store i64 %13, i64* %12, align 8, !dbg !173
  %14 = bitcast %struct.timeval* %initial_tv to i8*, !dbg !173
  %15 = bitcast %struct.timeval* %coerce to i8*, !dbg !173
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* %15, i64 16, i32 8, i1 false), !dbg !174
  br label %if.end12, !dbg !176

if.end12:                                         ; preds = %if.then9, %if.end6
  store i32 0, i32* %num, align 4, !dbg !177
  %16 = load i32, i32* %readfd0.addr, align 4, !dbg !178
  %cmp13 = icmp ne i32 %16, -1, !dbg !180
  br i1 %cmp13, label %if.then15, label %if.end20, !dbg !181

if.then15:                                        ; preds = %if.end12
  %17 = load i32, i32* %readfd0.addr, align 4, !dbg !182
  %18 = load i32, i32* %num, align 4, !dbg !184
  %idxprom = sext i32 %18 to i64, !dbg !185
  %arrayidx = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom, !dbg !185
  %fd = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx, i32 0, i32 0, !dbg !186
  store i32 %17, i32* %fd, align 8, !dbg !187
  %19 = load i32, i32* %num, align 4, !dbg !188
  %idxprom16 = sext i32 %19 to i64, !dbg !189
  %arrayidx17 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom16, !dbg !189
  %events = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx17, i32 0, i32 1, !dbg !190
  store i16 195, i16* %events, align 4, !dbg !191
  %20 = load i32, i32* %num, align 4, !dbg !192
  %idxprom18 = sext i32 %20 to i64, !dbg !193
  %arrayidx19 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom18, !dbg !193
  %revents = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx19, i32 0, i32 2, !dbg !194
  store i16 0, i16* %revents, align 2, !dbg !195
  %21 = load i32, i32* %num, align 4, !dbg !196
  %inc = add nsw i32 %21, 1, !dbg !196
  store i32 %inc, i32* %num, align 4, !dbg !196
  br label %if.end20, !dbg !197

if.end20:                                         ; preds = %if.then15, %if.end12
  %22 = load i32, i32* %readfd1.addr, align 4, !dbg !198
  %cmp21 = icmp ne i32 %22, -1, !dbg !200
  br i1 %cmp21, label %if.then23, label %if.end34, !dbg !201

if.then23:                                        ; preds = %if.end20
  %23 = load i32, i32* %readfd1.addr, align 4, !dbg !202
  %24 = load i32, i32* %num, align 4, !dbg !204
  %idxprom24 = sext i32 %24 to i64, !dbg !205
  %arrayidx25 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom24, !dbg !205
  %fd26 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx25, i32 0, i32 0, !dbg !206
  store i32 %23, i32* %fd26, align 8, !dbg !207
  %25 = load i32, i32* %num, align 4, !dbg !208
  %idxprom27 = sext i32 %25 to i64, !dbg !209
  %arrayidx28 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom27, !dbg !209
  %events29 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx28, i32 0, i32 1, !dbg !210
  store i16 195, i16* %events29, align 4, !dbg !211
  %26 = load i32, i32* %num, align 4, !dbg !212
  %idxprom30 = sext i32 %26 to i64, !dbg !213
  %arrayidx31 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom30, !dbg !213
  %revents32 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx31, i32 0, i32 2, !dbg !214
  store i16 0, i16* %revents32, align 2, !dbg !215
  %27 = load i32, i32* %num, align 4, !dbg !216
  %inc33 = add nsw i32 %27, 1, !dbg !216
  store i32 %inc33, i32* %num, align 4, !dbg !216
  br label %if.end34, !dbg !217

if.end34:                                         ; preds = %if.then23, %if.end20
  %28 = load i32, i32* %writefd.addr, align 4, !dbg !218
  %cmp35 = icmp ne i32 %28, -1, !dbg !220
  br i1 %cmp35, label %if.then37, label %if.end48, !dbg !221

if.then37:                                        ; preds = %if.end34
  %29 = load i32, i32* %writefd.addr, align 4, !dbg !222
  %30 = load i32, i32* %num, align 4, !dbg !224
  %idxprom38 = sext i32 %30 to i64, !dbg !225
  %arrayidx39 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom38, !dbg !225
  %fd40 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx39, i32 0, i32 0, !dbg !226
  store i32 %29, i32* %fd40, align 8, !dbg !227
  %31 = load i32, i32* %num, align 4, !dbg !228
  %idxprom41 = sext i32 %31 to i64, !dbg !229
  %arrayidx42 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom41, !dbg !229
  %events43 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx42, i32 0, i32 1, !dbg !230
  store i16 260, i16* %events43, align 4, !dbg !231
  %32 = load i32, i32* %num, align 4, !dbg !232
  %idxprom44 = sext i32 %32 to i64, !dbg !233
  %arrayidx45 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom44, !dbg !233
  %revents46 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx45, i32 0, i32 2, !dbg !234
  store i16 0, i16* %revents46, align 2, !dbg !235
  %33 = load i32, i32* %num, align 4, !dbg !236
  %inc47 = add nsw i32 %33, 1, !dbg !236
  store i32 %inc47, i32* %num, align 4, !dbg !236
  br label %if.end48, !dbg !237

if.end48:                                         ; preds = %if.then37, %if.end34
  br label %do.body, !dbg !238

do.body:                                          ; preds = %do.cond, %if.end48
  %34 = load i64, i64* %timeout_ms.addr, align 8, !dbg !239
  %cmp49 = icmp slt i64 %34, 0, !dbg !242
  br i1 %cmp49, label %if.then51, label %if.else, !dbg !243

if.then51:                                        ; preds = %do.body
  store i32 -1, i32* %pending_ms, align 4, !dbg !244
  br label %if.end54, !dbg !245

if.else:                                          ; preds = %do.body
  %35 = load i64, i64* %timeout_ms.addr, align 8, !dbg !246
  %tobool = icmp ne i64 %35, 0, !dbg !246
  br i1 %tobool, label %if.end53, label %if.then52, !dbg !248

if.then52:                                        ; preds = %if.else
  store i32 0, i32* %pending_ms, align 4, !dbg !249
  br label %if.end53, !dbg !250

if.end53:                                         ; preds = %if.then52, %if.else
  br label %if.end54

if.end54:                                         ; preds = %if.end53, %if.then51
  %arraydecay = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i32 0, i32 0, !dbg !251
  %36 = load i32, i32* %num, align 4, !dbg !252
  %conv55 = sext i32 %36 to i64, !dbg !252
  %37 = load i32, i32* %pending_ms, align 4, !dbg !253
  %call56 = call i32 @poll(%struct.pollfd* %arraydecay, i64 %conv55, i32 %37), !dbg !254
  store i32 %call56, i32* %r, align 4, !dbg !255
  %38 = load i32, i32* %r, align 4, !dbg !256
  %cmp57 = icmp ne i32 %38, -1, !dbg !258
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !259

if.then59:                                        ; preds = %if.end54
  br label %do.end, !dbg !260

if.end60:                                         ; preds = %if.end54
  %call61 = call i32* @__errno_location() #1, !dbg !261
  %39 = load i32, i32* %call61, align 4, !dbg !261
  store i32 %39, i32* %error, align 4, !dbg !262
  %40 = load i32, i32* %error, align 4, !dbg !263
  %tobool62 = icmp ne i32 %40, 0, !dbg !263
  br i1 %tobool62, label %land.lhs.true63, label %if.end68, !dbg !265

land.lhs.true63:                                  ; preds = %if.end60
  %41 = load i32, i32* @Curl_ack_eintr, align 4, !dbg !266
  %tobool64 = icmp ne i32 %41, 0, !dbg !266
  br i1 %tobool64, label %if.then67, label %lor.lhs.false, !dbg !266

lor.lhs.false:                                    ; preds = %land.lhs.true63
  %42 = load i32, i32* %error, align 4, !dbg !268
  %cmp65 = icmp ne i32 %42, 4, !dbg !268
  br i1 %cmp65, label %if.then67, label %if.end68, !dbg !270

if.then67:                                        ; preds = %lor.lhs.false, %land.lhs.true63
  br label %do.end, !dbg !271

if.end68:                                         ; preds = %lor.lhs.false, %if.end60
  %43 = load i64, i64* %timeout_ms.addr, align 8, !dbg !272
  %cmp69 = icmp sgt i64 %43, 0, !dbg !274
  br i1 %cmp69, label %if.then71, label %if.end81, !dbg !275

if.then71:                                        ; preds = %if.end68
  %44 = load i64, i64* %timeout_ms.addr, align 8, !dbg !276
  %call72 = call { i64, i64 } @curlx_tvnow(), !dbg !278
  %45 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !278
  %46 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %45, i32 0, i32 0, !dbg !278
  %47 = extractvalue { i64, i64 } %call72, 0, !dbg !278
  store i64 %47, i64* %46, align 8, !dbg !278
  %48 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %45, i32 0, i32 1, !dbg !278
  %49 = extractvalue { i64, i64 } %call72, 1, !dbg !278
  store i64 %49, i64* %48, align 8, !dbg !278
  %50 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !278
  %51 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %50, i32 0, i32 0, !dbg !278
  %52 = load i64, i64* %51, align 8, !dbg !278
  %53 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %50, i32 0, i32 1, !dbg !278
  %54 = load i64, i64* %53, align 8, !dbg !278
  %55 = bitcast %struct.timeval* %initial_tv to { i64, i64 }*, !dbg !278
  %56 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %55, i32 0, i32 0, !dbg !278
  %57 = load i64, i64* %56, align 8, !dbg !278
  %58 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %55, i32 0, i32 1, !dbg !278
  %59 = load i64, i64* %58, align 8, !dbg !278
  %call73 = call i64 @curlx_tvdiff(i64 %52, i64 %54, i64 %57, i64 %59), !dbg !279
  %conv74 = trunc i64 %call73 to i32, !dbg !278
  %conv75 = sext i32 %conv74 to i64, !dbg !278
  %sub = sub nsw i64 %44, %conv75, !dbg !281
  %conv76 = trunc i64 %sub to i32, !dbg !282
  store i32 %conv76, i32* %pending_ms, align 4, !dbg !283
  %60 = load i32, i32* %pending_ms, align 4, !dbg !284
  %cmp77 = icmp sle i32 %60, 0, !dbg !286
  br i1 %cmp77, label %if.then79, label %if.end80, !dbg !287

if.then79:                                        ; preds = %if.then71
  store i32 0, i32* %r, align 4, !dbg !288
  br label %do.end, !dbg !290

if.end80:                                         ; preds = %if.then71
  br label %if.end81, !dbg !291

if.end81:                                         ; preds = %if.end80, %if.end68
  br label %do.cond, !dbg !292

do.cond:                                          ; preds = %if.end81
  %61 = load i32, i32* %r, align 4, !dbg !293
  %cmp82 = icmp eq i32 %61, -1, !dbg !295
  br i1 %cmp82, label %do.body, label %do.end, !dbg !296

do.end:                                           ; preds = %do.cond, %if.then79, %if.then67, %if.then59
  %62 = load i32, i32* %r, align 4, !dbg !297
  %cmp84 = icmp slt i32 %62, 0, !dbg !299
  br i1 %cmp84, label %if.then86, label %if.end87, !dbg !300

if.then86:                                        ; preds = %do.end
  store i32 -1, i32* %retval, align 4, !dbg !301
  br label %return, !dbg !301

if.end87:                                         ; preds = %do.end
  %63 = load i32, i32* %r, align 4, !dbg !302
  %cmp88 = icmp eq i32 %63, 0, !dbg !304
  br i1 %cmp88, label %if.then90, label %if.end91, !dbg !305

if.then90:                                        ; preds = %if.end87
  store i32 0, i32* %retval, align 4, !dbg !306
  br label %return, !dbg !306

if.end91:                                         ; preds = %if.end87
  store i32 0, i32* %ret, align 4, !dbg !307
  store i32 0, i32* %num, align 4, !dbg !308
  %64 = load i32, i32* %readfd0.addr, align 4, !dbg !309
  %cmp92 = icmp ne i32 %64, -1, !dbg !311
  br i1 %cmp92, label %if.then94, label %if.end112, !dbg !312

if.then94:                                        ; preds = %if.end91
  %65 = load i32, i32* %num, align 4, !dbg !313
  %idxprom95 = sext i32 %65 to i64, !dbg !316
  %arrayidx96 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom95, !dbg !316
  %revents97 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx96, i32 0, i32 2, !dbg !317
  %66 = load i16, i16* %revents97, align 2, !dbg !317
  %conv98 = sext i16 %66 to i32, !dbg !316
  %and = and i32 %conv98, 89, !dbg !318
  %tobool99 = icmp ne i32 %and, 0, !dbg !318
  br i1 %tobool99, label %if.then100, label %if.end101, !dbg !319

if.then100:                                       ; preds = %if.then94
  %67 = load i32, i32* %ret, align 4, !dbg !320
  %or = or i32 %67, 1, !dbg !320
  store i32 %or, i32* %ret, align 4, !dbg !320
  br label %if.end101, !dbg !321

if.end101:                                        ; preds = %if.then100, %if.then94
  %68 = load i32, i32* %num, align 4, !dbg !322
  %idxprom102 = sext i32 %68 to i64, !dbg !324
  %arrayidx103 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom102, !dbg !324
  %revents104 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx103, i32 0, i32 2, !dbg !325
  %69 = load i16, i16* %revents104, align 2, !dbg !325
  %conv105 = sext i16 %69 to i32, !dbg !324
  %and106 = and i32 %conv105, 162, !dbg !326
  %tobool107 = icmp ne i32 %and106, 0, !dbg !326
  br i1 %tobool107, label %if.then108, label %if.end110, !dbg !327

if.then108:                                       ; preds = %if.end101
  %70 = load i32, i32* %ret, align 4, !dbg !328
  %or109 = or i32 %70, 4, !dbg !328
  store i32 %or109, i32* %ret, align 4, !dbg !328
  br label %if.end110, !dbg !329

if.end110:                                        ; preds = %if.then108, %if.end101
  %71 = load i32, i32* %num, align 4, !dbg !330
  %inc111 = add nsw i32 %71, 1, !dbg !330
  store i32 %inc111, i32* %num, align 4, !dbg !330
  br label %if.end112, !dbg !331

if.end112:                                        ; preds = %if.end110, %if.end91
  %72 = load i32, i32* %readfd1.addr, align 4, !dbg !332
  %cmp113 = icmp ne i32 %72, -1, !dbg !334
  br i1 %cmp113, label %if.then115, label %if.end135, !dbg !335

if.then115:                                       ; preds = %if.end112
  %73 = load i32, i32* %num, align 4, !dbg !336
  %idxprom116 = sext i32 %73 to i64, !dbg !339
  %arrayidx117 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom116, !dbg !339
  %revents118 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx117, i32 0, i32 2, !dbg !340
  %74 = load i16, i16* %revents118, align 2, !dbg !340
  %conv119 = sext i16 %74 to i32, !dbg !339
  %and120 = and i32 %conv119, 89, !dbg !341
  %tobool121 = icmp ne i32 %and120, 0, !dbg !341
  br i1 %tobool121, label %if.then122, label %if.end124, !dbg !342

if.then122:                                       ; preds = %if.then115
  %75 = load i32, i32* %ret, align 4, !dbg !343
  %or123 = or i32 %75, 8, !dbg !343
  store i32 %or123, i32* %ret, align 4, !dbg !343
  br label %if.end124, !dbg !344

if.end124:                                        ; preds = %if.then122, %if.then115
  %76 = load i32, i32* %num, align 4, !dbg !345
  %idxprom125 = sext i32 %76 to i64, !dbg !347
  %arrayidx126 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom125, !dbg !347
  %revents127 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx126, i32 0, i32 2, !dbg !348
  %77 = load i16, i16* %revents127, align 2, !dbg !348
  %conv128 = sext i16 %77 to i32, !dbg !347
  %and129 = and i32 %conv128, 162, !dbg !349
  %tobool130 = icmp ne i32 %and129, 0, !dbg !349
  br i1 %tobool130, label %if.then131, label %if.end133, !dbg !350

if.then131:                                       ; preds = %if.end124
  %78 = load i32, i32* %ret, align 4, !dbg !351
  %or132 = or i32 %78, 4, !dbg !351
  store i32 %or132, i32* %ret, align 4, !dbg !351
  br label %if.end133, !dbg !352

if.end133:                                        ; preds = %if.then131, %if.end124
  %79 = load i32, i32* %num, align 4, !dbg !353
  %inc134 = add nsw i32 %79, 1, !dbg !353
  store i32 %inc134, i32* %num, align 4, !dbg !353
  br label %if.end135, !dbg !354

if.end135:                                        ; preds = %if.end133, %if.end112
  %80 = load i32, i32* %writefd.addr, align 4, !dbg !355
  %cmp136 = icmp ne i32 %80, -1, !dbg !357
  br i1 %cmp136, label %if.then138, label %if.end157, !dbg !358

if.then138:                                       ; preds = %if.end135
  %81 = load i32, i32* %num, align 4, !dbg !359
  %idxprom139 = sext i32 %81 to i64, !dbg !362
  %arrayidx140 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom139, !dbg !362
  %revents141 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx140, i32 0, i32 2, !dbg !363
  %82 = load i16, i16* %revents141, align 2, !dbg !363
  %conv142 = sext i16 %82 to i32, !dbg !362
  %and143 = and i32 %conv142, 260, !dbg !364
  %tobool144 = icmp ne i32 %and143, 0, !dbg !364
  br i1 %tobool144, label %if.then145, label %if.end147, !dbg !365

if.then145:                                       ; preds = %if.then138
  %83 = load i32, i32* %ret, align 4, !dbg !366
  %or146 = or i32 %83, 2, !dbg !366
  store i32 %or146, i32* %ret, align 4, !dbg !366
  br label %if.end147, !dbg !367

if.end147:                                        ; preds = %if.then145, %if.then138
  %84 = load i32, i32* %num, align 4, !dbg !368
  %idxprom148 = sext i32 %84 to i64, !dbg !370
  %arrayidx149 = getelementptr inbounds [3 x %struct.pollfd], [3 x %struct.pollfd]* %pfd, i64 0, i64 %idxprom148, !dbg !370
  %revents150 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx149, i32 0, i32 2, !dbg !371
  %85 = load i16, i16* %revents150, align 2, !dbg !371
  %conv151 = sext i16 %85 to i32, !dbg !370
  %and152 = and i32 %conv151, 56, !dbg !372
  %tobool153 = icmp ne i32 %and152, 0, !dbg !372
  br i1 %tobool153, label %if.then154, label %if.end156, !dbg !373

if.then154:                                       ; preds = %if.end147
  %86 = load i32, i32* %ret, align 4, !dbg !374
  %or155 = or i32 %86, 4, !dbg !374
  store i32 %or155, i32* %ret, align 4, !dbg !374
  br label %if.end156, !dbg !375

if.end156:                                        ; preds = %if.then154, %if.end147
  br label %if.end157, !dbg !376

if.end157:                                        ; preds = %if.end156, %if.end135
  %87 = load i32, i32* %ret, align 4, !dbg !377
  store i32 %87, i32* %retval, align 4, !dbg !378
  br label %return, !dbg !378

return:                                           ; preds = %if.end157, %if.then90, %if.then86, %if.then5
  %88 = load i32, i32* %retval, align 4, !dbg !379
  ret i32 %88, !dbg !379
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define i32 @Curl_poll(%struct.pollfd* %ufds, i32 %nfds, i32 %timeout_ms) #0 !dbg !19 {
entry:
  %retval = alloca i32, align 4
  %ufds.addr = alloca %struct.pollfd*, align 8
  %nfds.addr = alloca i32, align 4
  %timeout_ms.addr = alloca i32, align 4
  %initial_tv = alloca %struct.timeval, align 8
  %fds_none = alloca i8, align 1
  %i = alloca i32, align 4
  %pending_ms = alloca i32, align 4
  %error = alloca i32, align 4
  %r = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  %agg.tmp = alloca %struct.timeval, align 8
  store %struct.pollfd* %ufds, %struct.pollfd** %ufds.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pollfd** %ufds.addr, metadata !380, metadata !37), !dbg !381
  store i32 %nfds, i32* %nfds.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nfds.addr, metadata !382, metadata !37), !dbg !383
  store i32 %timeout_ms, i32* %timeout_ms.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timeout_ms.addr, metadata !384, metadata !37), !dbg !385
  call void @llvm.dbg.declare(metadata %struct.timeval* %initial_tv, metadata !386, metadata !37), !dbg !387
  %0 = bitcast %struct.timeval* %initial_tv to i8*, !dbg !387
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 16, i32 8, i1 false), !dbg !387
  call void @llvm.dbg.declare(metadata i8* %fds_none, metadata !388, metadata !37), !dbg !390
  store i8 1, i8* %fds_none, align 1, !dbg !390
  call void @llvm.dbg.declare(metadata i32* %i, metadata !391, metadata !37), !dbg !392
  call void @llvm.dbg.declare(metadata i32* %pending_ms, metadata !393, metadata !37), !dbg !394
  store i32 0, i32* %pending_ms, align 4, !dbg !394
  call void @llvm.dbg.declare(metadata i32* %error, metadata !395, metadata !37), !dbg !396
  call void @llvm.dbg.declare(metadata i32* %r, metadata !397, metadata !37), !dbg !398
  %1 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !399
  %tobool = icmp ne %struct.pollfd* %1, null, !dbg !399
  br i1 %tobool, label %if.then, label %if.end3, !dbg !401

if.then:                                          ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !402
  br label %for.cond, !dbg !405

for.cond:                                         ; preds = %for.inc, %if.then
  %2 = load i32, i32* %i, align 4, !dbg !406
  %3 = load i32, i32* %nfds.addr, align 4, !dbg !409
  %cmp = icmp ult i32 %2, %3, !dbg !410
  br i1 %cmp, label %for.body, label %for.end, !dbg !411

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !412
  %idxprom = zext i32 %4 to i64, !dbg !415
  %5 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !415
  %arrayidx = getelementptr inbounds %struct.pollfd, %struct.pollfd* %5, i64 %idxprom, !dbg !415
  %fd = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx, i32 0, i32 0, !dbg !416
  %6 = load i32, i32* %fd, align 4, !dbg !416
  %cmp1 = icmp ne i32 %6, -1, !dbg !417
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !418

if.then2:                                         ; preds = %for.body
  store i8 0, i8* %fds_none, align 1, !dbg !419
  br label %for.end, !dbg !421

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !422

for.inc:                                          ; preds = %if.end
  %7 = load i32, i32* %i, align 4, !dbg !423
  %inc = add i32 %7, 1, !dbg !423
  store i32 %inc, i32* %i, align 4, !dbg !423
  br label %for.cond, !dbg !425

for.end:                                          ; preds = %if.then2, %for.cond
  br label %if.end3, !dbg !426

if.end3:                                          ; preds = %for.end, %entry
  %8 = load i8, i8* %fds_none, align 1, !dbg !427
  %tobool4 = trunc i8 %8 to i1, !dbg !427
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !429

if.then5:                                         ; preds = %if.end3
  %9 = load i32, i32* %timeout_ms.addr, align 4, !dbg !430
  %call = call i32 @Curl_wait_ms(i32 %9), !dbg !432
  store i32 %call, i32* %r, align 4, !dbg !433
  %10 = load i32, i32* %r, align 4, !dbg !434
  store i32 %10, i32* %retval, align 4, !dbg !435
  br label %return, !dbg !435

if.end6:                                          ; preds = %if.end3
  %11 = load i32, i32* %timeout_ms.addr, align 4, !dbg !436
  %cmp7 = icmp sgt i32 %11, 0, !dbg !438
  br i1 %cmp7, label %if.then8, label %if.end10, !dbg !439

if.then8:                                         ; preds = %if.end6
  %12 = load i32, i32* %timeout_ms.addr, align 4, !dbg !440
  store i32 %12, i32* %pending_ms, align 4, !dbg !442
  %call9 = call { i64, i64 } @curlx_tvnow(), !dbg !443
  %13 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !443
  %14 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %13, i32 0, i32 0, !dbg !443
  %15 = extractvalue { i64, i64 } %call9, 0, !dbg !443
  store i64 %15, i64* %14, align 8, !dbg !443
  %16 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %13, i32 0, i32 1, !dbg !443
  %17 = extractvalue { i64, i64 } %call9, 1, !dbg !443
  store i64 %17, i64* %16, align 8, !dbg !443
  %18 = bitcast %struct.timeval* %initial_tv to i8*, !dbg !443
  %19 = bitcast %struct.timeval* %coerce to i8*, !dbg !443
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %18, i8* %19, i64 16, i32 8, i1 false), !dbg !444
  br label %if.end10, !dbg !446

if.end10:                                         ; preds = %if.then8, %if.end6
  br label %do.body, !dbg !447

do.body:                                          ; preds = %do.cond, %if.end10
  %20 = load i32, i32* %timeout_ms.addr, align 4, !dbg !448
  %cmp11 = icmp slt i32 %20, 0, !dbg !451
  br i1 %cmp11, label %if.then12, label %if.else, !dbg !452

if.then12:                                        ; preds = %do.body
  store i32 -1, i32* %pending_ms, align 4, !dbg !453
  br label %if.end16, !dbg !454

if.else:                                          ; preds = %do.body
  %21 = load i32, i32* %timeout_ms.addr, align 4, !dbg !455
  %tobool13 = icmp ne i32 %21, 0, !dbg !455
  br i1 %tobool13, label %if.end15, label %if.then14, !dbg !457

if.then14:                                        ; preds = %if.else
  store i32 0, i32* %pending_ms, align 4, !dbg !458
  br label %if.end15, !dbg !459

if.end15:                                         ; preds = %if.then14, %if.else
  br label %if.end16

if.end16:                                         ; preds = %if.end15, %if.then12
  %22 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !460
  %23 = load i32, i32* %nfds.addr, align 4, !dbg !461
  %conv = zext i32 %23 to i64, !dbg !461
  %24 = load i32, i32* %pending_ms, align 4, !dbg !462
  %call17 = call i32 @poll(%struct.pollfd* %22, i64 %conv, i32 %24), !dbg !463
  store i32 %call17, i32* %r, align 4, !dbg !464
  %25 = load i32, i32* %r, align 4, !dbg !465
  %cmp18 = icmp ne i32 %25, -1, !dbg !467
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !468

if.then20:                                        ; preds = %if.end16
  br label %do.end, !dbg !469

if.end21:                                         ; preds = %if.end16
  %call22 = call i32* @__errno_location() #1, !dbg !470
  %26 = load i32, i32* %call22, align 4, !dbg !470
  store i32 %26, i32* %error, align 4, !dbg !471
  %27 = load i32, i32* %error, align 4, !dbg !472
  %tobool23 = icmp ne i32 %27, 0, !dbg !472
  br i1 %tobool23, label %land.lhs.true, label %if.end28, !dbg !474

land.lhs.true:                                    ; preds = %if.end21
  %28 = load i32, i32* @Curl_ack_eintr, align 4, !dbg !475
  %tobool24 = icmp ne i32 %28, 0, !dbg !475
  br i1 %tobool24, label %if.then27, label %lor.lhs.false, !dbg !475

lor.lhs.false:                                    ; preds = %land.lhs.true
  %29 = load i32, i32* %error, align 4, !dbg !477
  %cmp25 = icmp ne i32 %29, 4, !dbg !477
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !479

if.then27:                                        ; preds = %lor.lhs.false, %land.lhs.true
  br label %do.end, !dbg !480

if.end28:                                         ; preds = %lor.lhs.false, %if.end21
  %30 = load i32, i32* %timeout_ms.addr, align 4, !dbg !481
  %cmp29 = icmp sgt i32 %30, 0, !dbg !483
  br i1 %cmp29, label %if.then31, label %if.end39, !dbg !484

if.then31:                                        ; preds = %if.end28
  %31 = load i32, i32* %timeout_ms.addr, align 4, !dbg !485
  %call32 = call { i64, i64 } @curlx_tvnow(), !dbg !487
  %32 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !487
  %33 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %32, i32 0, i32 0, !dbg !487
  %34 = extractvalue { i64, i64 } %call32, 0, !dbg !487
  store i64 %34, i64* %33, align 8, !dbg !487
  %35 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %32, i32 0, i32 1, !dbg !487
  %36 = extractvalue { i64, i64 } %call32, 1, !dbg !487
  store i64 %36, i64* %35, align 8, !dbg !487
  %37 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !487
  %38 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %37, i32 0, i32 0, !dbg !487
  %39 = load i64, i64* %38, align 8, !dbg !487
  %40 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %37, i32 0, i32 1, !dbg !487
  %41 = load i64, i64* %40, align 8, !dbg !487
  %42 = bitcast %struct.timeval* %initial_tv to { i64, i64 }*, !dbg !487
  %43 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %42, i32 0, i32 0, !dbg !487
  %44 = load i64, i64* %43, align 8, !dbg !487
  %45 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %42, i32 0, i32 1, !dbg !487
  %46 = load i64, i64* %45, align 8, !dbg !487
  %call33 = call i64 @curlx_tvdiff(i64 %39, i64 %41, i64 %44, i64 %46), !dbg !488
  %conv34 = trunc i64 %call33 to i32, !dbg !487
  %sub = sub nsw i32 %31, %conv34, !dbg !490
  store i32 %sub, i32* %pending_ms, align 4, !dbg !491
  %47 = load i32, i32* %pending_ms, align 4, !dbg !492
  %cmp35 = icmp sle i32 %47, 0, !dbg !494
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !495

if.then37:                                        ; preds = %if.then31
  store i32 0, i32* %r, align 4, !dbg !496
  br label %do.end, !dbg !498

if.end38:                                         ; preds = %if.then31
  br label %if.end39, !dbg !499

if.end39:                                         ; preds = %if.end38, %if.end28
  br label %do.cond, !dbg !500

do.cond:                                          ; preds = %if.end39
  %48 = load i32, i32* %r, align 4, !dbg !501
  %cmp40 = icmp eq i32 %48, -1, !dbg !503
  br i1 %cmp40, label %do.body, label %do.end, !dbg !504

do.end:                                           ; preds = %do.cond, %if.then37, %if.then27, %if.then20
  %49 = load i32, i32* %r, align 4, !dbg !505
  %cmp42 = icmp slt i32 %49, 0, !dbg !507
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !508

if.then44:                                        ; preds = %do.end
  store i32 -1, i32* %retval, align 4, !dbg !509
  br label %return, !dbg !509

if.end45:                                         ; preds = %do.end
  %50 = load i32, i32* %r, align 4, !dbg !510
  %cmp46 = icmp eq i32 %50, 0, !dbg !512
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !513

if.then48:                                        ; preds = %if.end45
  store i32 0, i32* %retval, align 4, !dbg !514
  br label %return, !dbg !514

if.end49:                                         ; preds = %if.end45
  store i32 0, i32* %i, align 4, !dbg !515
  br label %for.cond50, !dbg !517

for.cond50:                                       ; preds = %for.inc86, %if.end49
  %51 = load i32, i32* %i, align 4, !dbg !518
  %52 = load i32, i32* %nfds.addr, align 4, !dbg !521
  %cmp51 = icmp ult i32 %51, %52, !dbg !522
  br i1 %cmp51, label %for.body53, label %for.end88, !dbg !523

for.body53:                                       ; preds = %for.cond50
  %53 = load i32, i32* %i, align 4, !dbg !524
  %idxprom54 = zext i32 %53 to i64, !dbg !527
  %54 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !527
  %arrayidx55 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %54, i64 %idxprom54, !dbg !527
  %fd56 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx55, i32 0, i32 0, !dbg !528
  %55 = load i32, i32* %fd56, align 4, !dbg !528
  %cmp57 = icmp eq i32 %55, -1, !dbg !529
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !530

if.then59:                                        ; preds = %for.body53
  br label %for.inc86, !dbg !531

if.end60:                                         ; preds = %for.body53
  %56 = load i32, i32* %i, align 4, !dbg !532
  %idxprom61 = zext i32 %56 to i64, !dbg !534
  %57 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !534
  %arrayidx62 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %57, i64 %idxprom61, !dbg !534
  %revents = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx62, i32 0, i32 2, !dbg !535
  %58 = load i16, i16* %revents, align 2, !dbg !535
  %conv63 = sext i16 %58 to i32, !dbg !534
  %and = and i32 %conv63, 16, !dbg !536
  %tobool64 = icmp ne i32 %and, 0, !dbg !536
  br i1 %tobool64, label %if.then65, label %if.end71, !dbg !537

if.then65:                                        ; preds = %if.end60
  %59 = load i32, i32* %i, align 4, !dbg !538
  %idxprom66 = zext i32 %59 to i64, !dbg !539
  %60 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !539
  %arrayidx67 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %60, i64 %idxprom66, !dbg !539
  %revents68 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx67, i32 0, i32 2, !dbg !540
  %61 = load i16, i16* %revents68, align 2, !dbg !541
  %conv69 = sext i16 %61 to i32, !dbg !541
  %or = or i32 %conv69, 1, !dbg !541
  %conv70 = trunc i32 %or to i16, !dbg !541
  store i16 %conv70, i16* %revents68, align 2, !dbg !541
  br label %if.end71, !dbg !539

if.end71:                                         ; preds = %if.then65, %if.end60
  %62 = load i32, i32* %i, align 4, !dbg !542
  %idxprom72 = zext i32 %62 to i64, !dbg !544
  %63 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !544
  %arrayidx73 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %63, i64 %idxprom72, !dbg !544
  %revents74 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx73, i32 0, i32 2, !dbg !545
  %64 = load i16, i16* %revents74, align 2, !dbg !545
  %conv75 = sext i16 %64 to i32, !dbg !544
  %and76 = and i32 %conv75, 8, !dbg !546
  %tobool77 = icmp ne i32 %and76, 0, !dbg !546
  br i1 %tobool77, label %if.then78, label %if.end85, !dbg !547

if.then78:                                        ; preds = %if.end71
  %65 = load i32, i32* %i, align 4, !dbg !548
  %idxprom79 = zext i32 %65 to i64, !dbg !549
  %66 = load %struct.pollfd*, %struct.pollfd** %ufds.addr, align 8, !dbg !549
  %arrayidx80 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %66, i64 %idxprom79, !dbg !549
  %revents81 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %arrayidx80, i32 0, i32 2, !dbg !550
  %67 = load i16, i16* %revents81, align 2, !dbg !551
  %conv82 = sext i16 %67 to i32, !dbg !551
  %or83 = or i32 %conv82, 5, !dbg !551
  %conv84 = trunc i32 %or83 to i16, !dbg !551
  store i16 %conv84, i16* %revents81, align 2, !dbg !551
  br label %if.end85, !dbg !549

if.end85:                                         ; preds = %if.then78, %if.end71
  br label %for.inc86, !dbg !552

for.inc86:                                        ; preds = %if.end85, %if.then59
  %68 = load i32, i32* %i, align 4, !dbg !553
  %inc87 = add i32 %68, 1, !dbg !553
  store i32 %inc87, i32* %i, align 4, !dbg !553
  br label %for.cond50, !dbg !555

for.end88:                                        ; preds = %for.cond50
  %69 = load i32, i32* %r, align 4, !dbg !556
  store i32 %69, i32* %retval, align 4, !dbg !557
  br label %return, !dbg !557

return:                                           ; preds = %for.end88, %if.then48, %if.then44, %if.then5
  %70 = load i32, i32* %retval, align 4, !dbg !558
  ret i32 %70, !dbg !558
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!33, !34}
!llvm.ident = !{!35}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !31)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/select.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!5 = !{!6, !9, !19}
!6 = distinct !DISubprogram(name: "Curl_wait_ms", scope: !1, file: !1, line: 75, type: !7, isLocal: false, isDefinition: true, scopeLine: 76, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!4, !4}
!9 = distinct !DISubprogram(name: "Curl_socket_check", scope: !1, file: !1, line: 145, type: !10, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!10 = !DISubroutineType(types: !11)
!11 = !{!4, !12, !12, !12, !14}
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !13, line: 131, baseType: !4)
!13 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !15, line: 75, baseType: !16)
!15 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !17, line: 139, baseType: !18)
!17 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!18 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!19 = distinct !DISubprogram(name: "Curl_poll", scope: !1, file: !1, line: 391, type: !20, isLocal: false, isDefinition: true, scopeLine: 392, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!4, !22, !30, !4}
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DICompositeType(tag: DW_TAG_structure_type, name: "pollfd", file: !24, line: 39, size: 64, align: 32, elements: !25)
!24 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/poll.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!25 = !{!26, !27, !29}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !23, file: !24, line: 41, baseType: !4, size: 32, align: 32)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !23, file: !24, line: 42, baseType: !28, size: 16, align: 16, offset: 32)
!28 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "revents", scope: !23, file: !24, line: 43, baseType: !28, size: 16, align: 16, offset: 48)
!30 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!31 = !{!32}
!32 = !DIGlobalVariable(name: "Curl_ack_eintr", scope: !0, file: !1, line: 56, type: !4, isLocal: false, isDefinition: true, variable: i32* @Curl_ack_eintr)
!33 = !{i32 2, !"Dwarf Version", i32 4}
!34 = !{i32 2, !"Debug Info Version", i32 3}
!35 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!36 = !DILocalVariable(name: "timeout_ms", arg: 1, scope: !6, file: !1, line: 75, type: !4)
!37 = !DIExpression()
!38 = !DILocation(line: 75, column: 22, scope: !6)
!39 = !DILocalVariable(name: "initial_tv", scope: !6, file: !1, line: 81, type: !40)
!40 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !41, line: 30, size: 128, align: 64, elements: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!42 = !{!43, !44}
!43 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !40, file: !41, line: 32, baseType: !16, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !40, file: !41, line: 33, baseType: !45, size: 64, align: 64, offset: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !17, line: 141, baseType: !18)
!46 = !DILocation(line: 81, column: 18, scope: !6)
!47 = !DILocalVariable(name: "pending_ms", scope: !6, file: !1, line: 82, type: !4)
!48 = !DILocation(line: 82, column: 7, scope: !6)
!49 = !DILocalVariable(name: "error", scope: !6, file: !1, line: 83, type: !4)
!50 = !DILocation(line: 83, column: 7, scope: !6)
!51 = !DILocalVariable(name: "r", scope: !6, file: !1, line: 85, type: !4)
!52 = !DILocation(line: 85, column: 7, scope: !6)
!53 = !DILocation(line: 87, column: 7, scope: !54)
!54 = distinct !DILexicalBlock(scope: !6, file: !1, line: 87, column: 6)
!55 = !DILocation(line: 87, column: 6, scope: !6)
!56 = !DILocation(line: 88, column: 5, scope: !54)
!57 = !DILocation(line: 89, column: 6, scope: !58)
!58 = distinct !DILexicalBlock(scope: !6, file: !1, line: 89, column: 6)
!59 = !DILocation(line: 89, column: 17, scope: !58)
!60 = !DILocation(line: 89, column: 6, scope: !6)
!61 = !DILocation(line: 90, column: 5, scope: !62)
!62 = distinct !DILexicalBlock(scope: !58, file: !1, line: 89, column: 22)
!63 = !DILocation(line: 91, column: 5, scope: !62)
!64 = !DILocation(line: 98, column: 16, scope: !6)
!65 = !DILocation(line: 98, column: 14, scope: !6)
!66 = !DILocation(line: 99, column: 16, scope: !6)
!67 = !DILocation(line: 99, column: 16, scope: !68)
!68 = !DILexicalBlockFile(scope: !6, file: !1, discriminator: 1)
!69 = !DILocation(line: 100, column: 3, scope: !6)
!70 = !DILocation(line: 102, column: 23, scope: !71)
!71 = distinct !DILexicalBlock(scope: !6, file: !1, line: 100, column: 6)
!72 = !DILocation(line: 102, column: 9, scope: !71)
!73 = !DILocation(line: 102, column: 7, scope: !71)
!74 = !DILocation(line: 108, column: 8, scope: !75)
!75 = distinct !DILexicalBlock(scope: !71, file: !1, line: 108, column: 8)
!76 = !DILocation(line: 108, column: 10, scope: !75)
!77 = !DILocation(line: 108, column: 8, scope: !71)
!78 = !DILocation(line: 109, column: 7, scope: !75)
!79 = !DILocation(line: 110, column: 13, scope: !71)
!80 = !DILocation(line: 110, column: 11, scope: !71)
!81 = !DILocation(line: 111, column: 8, scope: !82)
!82 = distinct !DILexicalBlock(scope: !71, file: !1, line: 111, column: 8)
!83 = !DILocation(line: 111, column: 14, scope: !82)
!84 = !DILocation(line: 111, column: 17, scope: !85)
!85 = !DILexicalBlockFile(scope: !82, file: !1, discriminator: 1)
!86 = !DILocation(line: 111, column: 17, scope: !87)
!87 = !DILexicalBlockFile(scope: !82, file: !1, discriminator: 2)
!88 = !DILocation(line: 111, column: 8, scope: !87)
!89 = !DILocation(line: 112, column: 7, scope: !82)
!90 = !DILocation(line: 113, column: 18, scope: !71)
!91 = !DILocation(line: 113, column: 31, scope: !71)
!92 = !DILocation(line: 113, column: 31, scope: !93)
!93 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 1)
!94 = !DILocation(line: 113, column: 29, scope: !71)
!95 = !DILocation(line: 113, column: 16, scope: !71)
!96 = !DILocation(line: 114, column: 8, scope: !97)
!97 = distinct !DILexicalBlock(scope: !71, file: !1, line: 114, column: 8)
!98 = !DILocation(line: 114, column: 19, scope: !97)
!99 = !DILocation(line: 114, column: 8, scope: !71)
!100 = !DILocation(line: 115, column: 9, scope: !101)
!101 = distinct !DILexicalBlock(scope: !97, file: !1, line: 114, column: 25)
!102 = !DILocation(line: 116, column: 7, scope: !101)
!103 = !DILocation(line: 118, column: 3, scope: !71)
!104 = !DILocation(line: 118, column: 11, scope: !68)
!105 = !DILocation(line: 118, column: 13, scope: !68)
!106 = !DILocation(line: 118, column: 3, scope: !68)
!107 = !DILocation(line: 120, column: 6, scope: !108)
!108 = distinct !DILexicalBlock(scope: !6, file: !1, line: 120, column: 6)
!109 = !DILocation(line: 120, column: 6, scope: !6)
!110 = !DILocation(line: 121, column: 7, scope: !108)
!111 = !DILocation(line: 121, column: 5, scope: !108)
!112 = !DILocation(line: 122, column: 10, scope: !6)
!113 = !DILocation(line: 122, column: 3, scope: !6)
!114 = !DILocation(line: 123, column: 1, scope: !6)
!115 = !DILocalVariable(name: "readfd0", arg: 1, scope: !9, file: !1, line: 145, type: !12)
!116 = !DILocation(line: 145, column: 37, scope: !9)
!117 = !DILocalVariable(name: "readfd1", arg: 2, scope: !9, file: !1, line: 146, type: !12)
!118 = !DILocation(line: 146, column: 37, scope: !9)
!119 = !DILocalVariable(name: "writefd", arg: 3, scope: !9, file: !1, line: 147, type: !12)
!120 = !DILocation(line: 147, column: 37, scope: !9)
!121 = !DILocalVariable(name: "timeout_ms", arg: 4, scope: !9, file: !1, line: 148, type: !14)
!122 = !DILocation(line: 148, column: 30, scope: !9)
!123 = !DILocalVariable(name: "pfd", scope: !9, file: !1, line: 151, type: !124)
!124 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 192, align: 32, elements: !125)
!125 = !{!126}
!126 = !DISubrange(count: 3)
!127 = !DILocation(line: 151, column: 17, scope: !9)
!128 = !DILocalVariable(name: "num", scope: !9, file: !1, line: 152, type: !4)
!129 = !DILocation(line: 152, column: 7, scope: !9)
!130 = !DILocalVariable(name: "initial_tv", scope: !9, file: !1, line: 161, type: !40)
!131 = !DILocation(line: 161, column: 18, scope: !9)
!132 = !DILocalVariable(name: "pending_ms", scope: !9, file: !1, line: 162, type: !4)
!133 = !DILocation(line: 162, column: 7, scope: !9)
!134 = !DILocalVariable(name: "error", scope: !9, file: !1, line: 163, type: !4)
!135 = !DILocation(line: 163, column: 7, scope: !9)
!136 = !DILocalVariable(name: "r", scope: !9, file: !1, line: 164, type: !4)
!137 = !DILocation(line: 164, column: 7, scope: !9)
!138 = !DILocalVariable(name: "ret", scope: !9, file: !1, line: 165, type: !4)
!139 = !DILocation(line: 165, column: 7, scope: !9)
!140 = !DILocation(line: 169, column: 6, scope: !141)
!141 = distinct !DILexicalBlock(scope: !9, file: !1, line: 169, column: 6)
!142 = !DILocation(line: 169, column: 17, scope: !141)
!143 = !DILocation(line: 169, column: 6, scope: !9)
!144 = !DILocation(line: 170, column: 16, scope: !141)
!145 = !DILocation(line: 170, column: 5, scope: !141)
!146 = !DILocation(line: 173, column: 7, scope: !147)
!147 = distinct !DILexicalBlock(scope: !9, file: !1, line: 173, column: 6)
!148 = !DILocation(line: 173, column: 15, scope: !147)
!149 = !DILocation(line: 173, column: 35, scope: !147)
!150 = !DILocation(line: 173, column: 39, scope: !151)
!151 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 1)
!152 = !DILocation(line: 173, column: 47, scope: !151)
!153 = !DILocation(line: 173, column: 67, scope: !151)
!154 = !DILocation(line: 174, column: 7, scope: !147)
!155 = !DILocation(line: 174, column: 15, scope: !147)
!156 = !DILocation(line: 173, column: 6, scope: !157)
!157 = !DILexicalBlockFile(scope: !9, file: !1, discriminator: 2)
!158 = !DILocation(line: 176, column: 27, scope: !159)
!159 = distinct !DILexicalBlock(scope: !147, file: !1, line: 174, column: 36)
!160 = !DILocation(line: 176, column: 22, scope: !159)
!161 = !DILocation(line: 176, column: 9, scope: !159)
!162 = !DILocation(line: 176, column: 7, scope: !159)
!163 = !DILocation(line: 177, column: 12, scope: !159)
!164 = !DILocation(line: 177, column: 5, scope: !159)
!165 = !DILocation(line: 185, column: 6, scope: !166)
!166 = distinct !DILexicalBlock(scope: !9, file: !1, line: 185, column: 6)
!167 = !DILocation(line: 185, column: 17, scope: !166)
!168 = !DILocation(line: 185, column: 6, scope: !9)
!169 = !DILocation(line: 186, column: 23, scope: !170)
!170 = distinct !DILexicalBlock(scope: !166, file: !1, line: 185, column: 22)
!171 = !DILocation(line: 186, column: 18, scope: !170)
!172 = !DILocation(line: 186, column: 16, scope: !170)
!173 = !DILocation(line: 187, column: 18, scope: !170)
!174 = !DILocation(line: 187, column: 18, scope: !175)
!175 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 1)
!176 = !DILocation(line: 188, column: 3, scope: !170)
!177 = !DILocation(line: 192, column: 7, scope: !9)
!178 = !DILocation(line: 193, column: 6, scope: !179)
!179 = distinct !DILexicalBlock(scope: !9, file: !1, line: 193, column: 6)
!180 = !DILocation(line: 193, column: 14, scope: !179)
!181 = !DILocation(line: 193, column: 6, scope: !9)
!182 = !DILocation(line: 194, column: 19, scope: !183)
!183 = distinct !DILexicalBlock(scope: !179, file: !1, line: 193, column: 34)
!184 = !DILocation(line: 194, column: 9, scope: !183)
!185 = !DILocation(line: 194, column: 5, scope: !183)
!186 = !DILocation(line: 194, column: 14, scope: !183)
!187 = !DILocation(line: 194, column: 17, scope: !183)
!188 = !DILocation(line: 195, column: 9, scope: !183)
!189 = !DILocation(line: 195, column: 5, scope: !183)
!190 = !DILocation(line: 195, column: 14, scope: !183)
!191 = !DILocation(line: 195, column: 21, scope: !183)
!192 = !DILocation(line: 196, column: 9, scope: !183)
!193 = !DILocation(line: 196, column: 5, scope: !183)
!194 = !DILocation(line: 196, column: 14, scope: !183)
!195 = !DILocation(line: 196, column: 22, scope: !183)
!196 = !DILocation(line: 197, column: 8, scope: !183)
!197 = !DILocation(line: 198, column: 3, scope: !183)
!198 = !DILocation(line: 199, column: 6, scope: !199)
!199 = distinct !DILexicalBlock(scope: !9, file: !1, line: 199, column: 6)
!200 = !DILocation(line: 199, column: 14, scope: !199)
!201 = !DILocation(line: 199, column: 6, scope: !9)
!202 = !DILocation(line: 200, column: 19, scope: !203)
!203 = distinct !DILexicalBlock(scope: !199, file: !1, line: 199, column: 34)
!204 = !DILocation(line: 200, column: 9, scope: !203)
!205 = !DILocation(line: 200, column: 5, scope: !203)
!206 = !DILocation(line: 200, column: 14, scope: !203)
!207 = !DILocation(line: 200, column: 17, scope: !203)
!208 = !DILocation(line: 201, column: 9, scope: !203)
!209 = !DILocation(line: 201, column: 5, scope: !203)
!210 = !DILocation(line: 201, column: 14, scope: !203)
!211 = !DILocation(line: 201, column: 21, scope: !203)
!212 = !DILocation(line: 202, column: 9, scope: !203)
!213 = !DILocation(line: 202, column: 5, scope: !203)
!214 = !DILocation(line: 202, column: 14, scope: !203)
!215 = !DILocation(line: 202, column: 22, scope: !203)
!216 = !DILocation(line: 203, column: 8, scope: !203)
!217 = !DILocation(line: 204, column: 3, scope: !203)
!218 = !DILocation(line: 205, column: 6, scope: !219)
!219 = distinct !DILexicalBlock(scope: !9, file: !1, line: 205, column: 6)
!220 = !DILocation(line: 205, column: 14, scope: !219)
!221 = !DILocation(line: 205, column: 6, scope: !9)
!222 = !DILocation(line: 206, column: 19, scope: !223)
!223 = distinct !DILexicalBlock(scope: !219, file: !1, line: 205, column: 34)
!224 = !DILocation(line: 206, column: 9, scope: !223)
!225 = !DILocation(line: 206, column: 5, scope: !223)
!226 = !DILocation(line: 206, column: 14, scope: !223)
!227 = !DILocation(line: 206, column: 17, scope: !223)
!228 = !DILocation(line: 207, column: 9, scope: !223)
!229 = !DILocation(line: 207, column: 5, scope: !223)
!230 = !DILocation(line: 207, column: 14, scope: !223)
!231 = !DILocation(line: 207, column: 21, scope: !223)
!232 = !DILocation(line: 208, column: 9, scope: !223)
!233 = !DILocation(line: 208, column: 5, scope: !223)
!234 = !DILocation(line: 208, column: 14, scope: !223)
!235 = !DILocation(line: 208, column: 22, scope: !223)
!236 = !DILocation(line: 209, column: 8, scope: !223)
!237 = !DILocation(line: 210, column: 3, scope: !223)
!238 = !DILocation(line: 212, column: 3, scope: !9)
!239 = !DILocation(line: 213, column: 8, scope: !240)
!240 = distinct !DILexicalBlock(scope: !241, file: !1, line: 213, column: 8)
!241 = distinct !DILexicalBlock(scope: !9, file: !1, line: 212, column: 6)
!242 = !DILocation(line: 213, column: 19, scope: !240)
!243 = !DILocation(line: 213, column: 8, scope: !241)
!244 = !DILocation(line: 214, column: 18, scope: !240)
!245 = !DILocation(line: 214, column: 7, scope: !240)
!246 = !DILocation(line: 215, column: 14, scope: !247)
!247 = distinct !DILexicalBlock(scope: !240, file: !1, line: 215, column: 13)
!248 = !DILocation(line: 215, column: 13, scope: !240)
!249 = !DILocation(line: 216, column: 18, scope: !247)
!250 = !DILocation(line: 216, column: 7, scope: !247)
!251 = !DILocation(line: 217, column: 14, scope: !241)
!252 = !DILocation(line: 217, column: 19, scope: !241)
!253 = !DILocation(line: 217, column: 24, scope: !241)
!254 = !DILocation(line: 217, column: 9, scope: !241)
!255 = !DILocation(line: 217, column: 7, scope: !241)
!256 = !DILocation(line: 218, column: 8, scope: !257)
!257 = distinct !DILexicalBlock(scope: !241, file: !1, line: 218, column: 8)
!258 = !DILocation(line: 218, column: 10, scope: !257)
!259 = !DILocation(line: 218, column: 8, scope: !241)
!260 = !DILocation(line: 219, column: 7, scope: !257)
!261 = !DILocation(line: 220, column: 13, scope: !241)
!262 = !DILocation(line: 220, column: 11, scope: !241)
!263 = !DILocation(line: 221, column: 8, scope: !264)
!264 = distinct !DILexicalBlock(scope: !241, file: !1, line: 221, column: 8)
!265 = !DILocation(line: 221, column: 14, scope: !264)
!266 = !DILocation(line: 221, column: 17, scope: !267)
!267 = !DILexicalBlockFile(scope: !264, file: !1, discriminator: 1)
!268 = !DILocation(line: 221, column: 17, scope: !269)
!269 = !DILexicalBlockFile(scope: !264, file: !1, discriminator: 2)
!270 = !DILocation(line: 221, column: 8, scope: !269)
!271 = !DILocation(line: 222, column: 7, scope: !264)
!272 = !DILocation(line: 223, column: 8, scope: !273)
!273 = distinct !DILexicalBlock(scope: !241, file: !1, line: 223, column: 8)
!274 = !DILocation(line: 223, column: 19, scope: !273)
!275 = !DILocation(line: 223, column: 8, scope: !241)
!276 = !DILocation(line: 224, column: 26, scope: !277)
!277 = distinct !DILexicalBlock(scope: !273, file: !1, line: 223, column: 24)
!278 = !DILocation(line: 224, column: 39, scope: !277)
!279 = !DILocation(line: 224, column: 39, scope: !280)
!280 = !DILexicalBlockFile(scope: !277, file: !1, discriminator: 1)
!281 = !DILocation(line: 224, column: 37, scope: !277)
!282 = !DILocation(line: 224, column: 20, scope: !277)
!283 = !DILocation(line: 224, column: 18, scope: !277)
!284 = !DILocation(line: 225, column: 10, scope: !285)
!285 = distinct !DILexicalBlock(scope: !277, file: !1, line: 225, column: 10)
!286 = !DILocation(line: 225, column: 21, scope: !285)
!287 = !DILocation(line: 225, column: 10, scope: !277)
!288 = !DILocation(line: 226, column: 11, scope: !289)
!289 = distinct !DILexicalBlock(scope: !285, file: !1, line: 225, column: 27)
!290 = !DILocation(line: 227, column: 9, scope: !289)
!291 = !DILocation(line: 229, column: 5, scope: !277)
!292 = !DILocation(line: 230, column: 3, scope: !241)
!293 = !DILocation(line: 230, column: 11, scope: !294)
!294 = !DILexicalBlockFile(scope: !9, file: !1, discriminator: 1)
!295 = !DILocation(line: 230, column: 13, scope: !294)
!296 = !DILocation(line: 230, column: 3, scope: !294)
!297 = !DILocation(line: 232, column: 6, scope: !298)
!298 = distinct !DILexicalBlock(scope: !9, file: !1, line: 232, column: 6)
!299 = !DILocation(line: 232, column: 8, scope: !298)
!300 = !DILocation(line: 232, column: 6, scope: !9)
!301 = !DILocation(line: 233, column: 5, scope: !298)
!302 = !DILocation(line: 234, column: 6, scope: !303)
!303 = distinct !DILexicalBlock(scope: !9, file: !1, line: 234, column: 6)
!304 = !DILocation(line: 234, column: 8, scope: !303)
!305 = !DILocation(line: 234, column: 6, scope: !9)
!306 = !DILocation(line: 235, column: 5, scope: !303)
!307 = !DILocation(line: 237, column: 7, scope: !9)
!308 = !DILocation(line: 238, column: 7, scope: !9)
!309 = !DILocation(line: 239, column: 6, scope: !310)
!310 = distinct !DILexicalBlock(scope: !9, file: !1, line: 239, column: 6)
!311 = !DILocation(line: 239, column: 14, scope: !310)
!312 = !DILocation(line: 239, column: 6, scope: !9)
!313 = !DILocation(line: 240, column: 12, scope: !314)
!314 = distinct !DILexicalBlock(scope: !315, file: !1, line: 240, column: 8)
!315 = distinct !DILexicalBlock(scope: !310, file: !1, line: 239, column: 34)
!316 = !DILocation(line: 240, column: 8, scope: !314)
!317 = !DILocation(line: 240, column: 17, scope: !314)
!318 = !DILocation(line: 240, column: 25, scope: !314)
!319 = !DILocation(line: 240, column: 8, scope: !315)
!320 = !DILocation(line: 241, column: 11, scope: !314)
!321 = !DILocation(line: 241, column: 7, scope: !314)
!322 = !DILocation(line: 242, column: 12, scope: !323)
!323 = distinct !DILexicalBlock(scope: !315, file: !1, line: 242, column: 8)
!324 = !DILocation(line: 242, column: 8, scope: !323)
!325 = !DILocation(line: 242, column: 17, scope: !323)
!326 = !DILocation(line: 242, column: 25, scope: !323)
!327 = !DILocation(line: 242, column: 8, scope: !315)
!328 = !DILocation(line: 243, column: 11, scope: !323)
!329 = !DILocation(line: 243, column: 7, scope: !323)
!330 = !DILocation(line: 244, column: 8, scope: !315)
!331 = !DILocation(line: 245, column: 3, scope: !315)
!332 = !DILocation(line: 246, column: 6, scope: !333)
!333 = distinct !DILexicalBlock(scope: !9, file: !1, line: 246, column: 6)
!334 = !DILocation(line: 246, column: 14, scope: !333)
!335 = !DILocation(line: 246, column: 6, scope: !9)
!336 = !DILocation(line: 247, column: 12, scope: !337)
!337 = distinct !DILexicalBlock(scope: !338, file: !1, line: 247, column: 8)
!338 = distinct !DILexicalBlock(scope: !333, file: !1, line: 246, column: 34)
!339 = !DILocation(line: 247, column: 8, scope: !337)
!340 = !DILocation(line: 247, column: 17, scope: !337)
!341 = !DILocation(line: 247, column: 25, scope: !337)
!342 = !DILocation(line: 247, column: 8, scope: !338)
!343 = !DILocation(line: 248, column: 11, scope: !337)
!344 = !DILocation(line: 248, column: 7, scope: !337)
!345 = !DILocation(line: 249, column: 12, scope: !346)
!346 = distinct !DILexicalBlock(scope: !338, file: !1, line: 249, column: 8)
!347 = !DILocation(line: 249, column: 8, scope: !346)
!348 = !DILocation(line: 249, column: 17, scope: !346)
!349 = !DILocation(line: 249, column: 25, scope: !346)
!350 = !DILocation(line: 249, column: 8, scope: !338)
!351 = !DILocation(line: 250, column: 11, scope: !346)
!352 = !DILocation(line: 250, column: 7, scope: !346)
!353 = !DILocation(line: 251, column: 8, scope: !338)
!354 = !DILocation(line: 252, column: 3, scope: !338)
!355 = !DILocation(line: 253, column: 6, scope: !356)
!356 = distinct !DILexicalBlock(scope: !9, file: !1, line: 253, column: 6)
!357 = !DILocation(line: 253, column: 14, scope: !356)
!358 = !DILocation(line: 253, column: 6, scope: !9)
!359 = !DILocation(line: 254, column: 12, scope: !360)
!360 = distinct !DILexicalBlock(scope: !361, file: !1, line: 254, column: 8)
!361 = distinct !DILexicalBlock(scope: !356, file: !1, line: 253, column: 34)
!362 = !DILocation(line: 254, column: 8, scope: !360)
!363 = !DILocation(line: 254, column: 17, scope: !360)
!364 = !DILocation(line: 254, column: 25, scope: !360)
!365 = !DILocation(line: 254, column: 8, scope: !361)
!366 = !DILocation(line: 255, column: 11, scope: !360)
!367 = !DILocation(line: 255, column: 7, scope: !360)
!368 = !DILocation(line: 256, column: 12, scope: !369)
!369 = distinct !DILexicalBlock(scope: !361, file: !1, line: 256, column: 8)
!370 = !DILocation(line: 256, column: 8, scope: !369)
!371 = !DILocation(line: 256, column: 17, scope: !369)
!372 = !DILocation(line: 256, column: 25, scope: !369)
!373 = !DILocation(line: 256, column: 8, scope: !361)
!374 = !DILocation(line: 257, column: 11, scope: !369)
!375 = !DILocation(line: 257, column: 7, scope: !369)
!376 = !DILocation(line: 258, column: 3, scope: !361)
!377 = !DILocation(line: 260, column: 10, scope: !9)
!378 = !DILocation(line: 260, column: 3, scope: !9)
!379 = !DILocation(line: 376, column: 1, scope: !9)
!380 = !DILocalVariable(name: "ufds", arg: 1, scope: !19, file: !1, line: 391, type: !22)
!381 = !DILocation(line: 391, column: 29, scope: !19)
!382 = !DILocalVariable(name: "nfds", arg: 2, scope: !19, file: !1, line: 391, type: !30)
!383 = !DILocation(line: 391, column: 50, scope: !19)
!384 = !DILocalVariable(name: "timeout_ms", arg: 3, scope: !19, file: !1, line: 391, type: !4)
!385 = !DILocation(line: 391, column: 60, scope: !19)
!386 = !DILocalVariable(name: "initial_tv", scope: !19, file: !1, line: 401, type: !40)
!387 = !DILocation(line: 401, column: 18, scope: !19)
!388 = !DILocalVariable(name: "fds_none", scope: !19, file: !1, line: 402, type: !389)
!389 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!390 = !DILocation(line: 402, column: 8, scope: !19)
!391 = !DILocalVariable(name: "i", scope: !19, file: !1, line: 403, type: !30)
!392 = !DILocation(line: 403, column: 16, scope: !19)
!393 = !DILocalVariable(name: "pending_ms", scope: !19, file: !1, line: 404, type: !4)
!394 = !DILocation(line: 404, column: 7, scope: !19)
!395 = !DILocalVariable(name: "error", scope: !19, file: !1, line: 405, type: !4)
!396 = !DILocation(line: 405, column: 7, scope: !19)
!397 = !DILocalVariable(name: "r", scope: !19, file: !1, line: 406, type: !4)
!398 = !DILocation(line: 406, column: 7, scope: !19)
!399 = !DILocation(line: 408, column: 6, scope: !400)
!400 = distinct !DILexicalBlock(scope: !19, file: !1, line: 408, column: 6)
!401 = !DILocation(line: 408, column: 6, scope: !19)
!402 = !DILocation(line: 409, column: 11, scope: !403)
!403 = distinct !DILexicalBlock(scope: !404, file: !1, line: 409, column: 5)
!404 = distinct !DILexicalBlock(scope: !400, file: !1, line: 408, column: 12)
!405 = !DILocation(line: 409, column: 9, scope: !403)
!406 = !DILocation(line: 409, column: 16, scope: !407)
!407 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 1)
!408 = distinct !DILexicalBlock(scope: !403, file: !1, line: 409, column: 5)
!409 = !DILocation(line: 409, column: 20, scope: !407)
!410 = !DILocation(line: 409, column: 18, scope: !407)
!411 = !DILocation(line: 409, column: 5, scope: !407)
!412 = !DILocation(line: 410, column: 15, scope: !413)
!413 = distinct !DILexicalBlock(scope: !414, file: !1, line: 410, column: 10)
!414 = distinct !DILexicalBlock(scope: !408, file: !1, line: 409, column: 31)
!415 = !DILocation(line: 410, column: 10, scope: !413)
!416 = !DILocation(line: 410, column: 18, scope: !413)
!417 = !DILocation(line: 410, column: 21, scope: !413)
!418 = !DILocation(line: 410, column: 10, scope: !414)
!419 = !DILocation(line: 411, column: 18, scope: !420)
!420 = distinct !DILexicalBlock(scope: !413, file: !1, line: 410, column: 41)
!421 = !DILocation(line: 412, column: 9, scope: !420)
!422 = !DILocation(line: 414, column: 5, scope: !414)
!423 = !DILocation(line: 409, column: 27, scope: !424)
!424 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 2)
!425 = !DILocation(line: 409, column: 5, scope: !424)
!426 = !DILocation(line: 415, column: 3, scope: !404)
!427 = !DILocation(line: 416, column: 6, scope: !428)
!428 = distinct !DILexicalBlock(scope: !19, file: !1, line: 416, column: 6)
!429 = !DILocation(line: 416, column: 6, scope: !19)
!430 = !DILocation(line: 417, column: 22, scope: !431)
!431 = distinct !DILexicalBlock(scope: !428, file: !1, line: 416, column: 16)
!432 = !DILocation(line: 417, column: 9, scope: !431)
!433 = !DILocation(line: 417, column: 7, scope: !431)
!434 = !DILocation(line: 418, column: 12, scope: !431)
!435 = !DILocation(line: 418, column: 5, scope: !431)
!436 = !DILocation(line: 426, column: 6, scope: !437)
!437 = distinct !DILexicalBlock(scope: !19, file: !1, line: 426, column: 6)
!438 = !DILocation(line: 426, column: 17, scope: !437)
!439 = !DILocation(line: 426, column: 6, scope: !19)
!440 = !DILocation(line: 427, column: 18, scope: !441)
!441 = distinct !DILexicalBlock(scope: !437, file: !1, line: 426, column: 22)
!442 = !DILocation(line: 427, column: 16, scope: !441)
!443 = !DILocation(line: 428, column: 18, scope: !441)
!444 = !DILocation(line: 428, column: 18, scope: !445)
!445 = !DILexicalBlockFile(scope: !441, file: !1, discriminator: 1)
!446 = !DILocation(line: 429, column: 3, scope: !441)
!447 = !DILocation(line: 433, column: 3, scope: !19)
!448 = !DILocation(line: 434, column: 8, scope: !449)
!449 = distinct !DILexicalBlock(scope: !450, file: !1, line: 434, column: 8)
!450 = distinct !DILexicalBlock(scope: !19, file: !1, line: 433, column: 6)
!451 = !DILocation(line: 434, column: 19, scope: !449)
!452 = !DILocation(line: 434, column: 8, scope: !450)
!453 = !DILocation(line: 435, column: 18, scope: !449)
!454 = !DILocation(line: 435, column: 7, scope: !449)
!455 = !DILocation(line: 436, column: 14, scope: !456)
!456 = distinct !DILexicalBlock(scope: !449, file: !1, line: 436, column: 13)
!457 = !DILocation(line: 436, column: 13, scope: !449)
!458 = !DILocation(line: 437, column: 18, scope: !456)
!459 = !DILocation(line: 437, column: 7, scope: !456)
!460 = !DILocation(line: 438, column: 14, scope: !450)
!461 = !DILocation(line: 438, column: 20, scope: !450)
!462 = !DILocation(line: 438, column: 26, scope: !450)
!463 = !DILocation(line: 438, column: 9, scope: !450)
!464 = !DILocation(line: 438, column: 7, scope: !450)
!465 = !DILocation(line: 439, column: 8, scope: !466)
!466 = distinct !DILexicalBlock(scope: !450, file: !1, line: 439, column: 8)
!467 = !DILocation(line: 439, column: 10, scope: !466)
!468 = !DILocation(line: 439, column: 8, scope: !450)
!469 = !DILocation(line: 440, column: 7, scope: !466)
!470 = !DILocation(line: 441, column: 13, scope: !450)
!471 = !DILocation(line: 441, column: 11, scope: !450)
!472 = !DILocation(line: 442, column: 8, scope: !473)
!473 = distinct !DILexicalBlock(scope: !450, file: !1, line: 442, column: 8)
!474 = !DILocation(line: 442, column: 14, scope: !473)
!475 = !DILocation(line: 442, column: 17, scope: !476)
!476 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 1)
!477 = !DILocation(line: 442, column: 17, scope: !478)
!478 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 2)
!479 = !DILocation(line: 442, column: 8, scope: !478)
!480 = !DILocation(line: 443, column: 7, scope: !473)
!481 = !DILocation(line: 444, column: 8, scope: !482)
!482 = distinct !DILexicalBlock(scope: !450, file: !1, line: 444, column: 8)
!483 = !DILocation(line: 444, column: 19, scope: !482)
!484 = !DILocation(line: 444, column: 8, scope: !450)
!485 = !DILocation(line: 445, column: 26, scope: !486)
!486 = distinct !DILexicalBlock(scope: !482, file: !1, line: 444, column: 24)
!487 = !DILocation(line: 445, column: 39, scope: !486)
!488 = !DILocation(line: 445, column: 39, scope: !489)
!489 = !DILexicalBlockFile(scope: !486, file: !1, discriminator: 1)
!490 = !DILocation(line: 445, column: 37, scope: !486)
!491 = !DILocation(line: 445, column: 18, scope: !486)
!492 = !DILocation(line: 446, column: 10, scope: !493)
!493 = distinct !DILexicalBlock(scope: !486, file: !1, line: 446, column: 10)
!494 = !DILocation(line: 446, column: 21, scope: !493)
!495 = !DILocation(line: 446, column: 10, scope: !486)
!496 = !DILocation(line: 447, column: 11, scope: !497)
!497 = distinct !DILexicalBlock(scope: !493, file: !1, line: 446, column: 27)
!498 = !DILocation(line: 448, column: 9, scope: !497)
!499 = !DILocation(line: 450, column: 5, scope: !486)
!500 = !DILocation(line: 451, column: 3, scope: !450)
!501 = !DILocation(line: 451, column: 11, scope: !502)
!502 = !DILexicalBlockFile(scope: !19, file: !1, discriminator: 1)
!503 = !DILocation(line: 451, column: 13, scope: !502)
!504 = !DILocation(line: 451, column: 3, scope: !502)
!505 = !DILocation(line: 453, column: 6, scope: !506)
!506 = distinct !DILexicalBlock(scope: !19, file: !1, line: 453, column: 6)
!507 = !DILocation(line: 453, column: 8, scope: !506)
!508 = !DILocation(line: 453, column: 6, scope: !19)
!509 = !DILocation(line: 454, column: 5, scope: !506)
!510 = !DILocation(line: 455, column: 6, scope: !511)
!511 = distinct !DILexicalBlock(scope: !19, file: !1, line: 455, column: 6)
!512 = !DILocation(line: 455, column: 8, scope: !511)
!513 = !DILocation(line: 455, column: 6, scope: !19)
!514 = !DILocation(line: 456, column: 5, scope: !511)
!515 = !DILocation(line: 458, column: 9, scope: !516)
!516 = distinct !DILexicalBlock(scope: !19, file: !1, line: 458, column: 3)
!517 = !DILocation(line: 458, column: 7, scope: !516)
!518 = !DILocation(line: 458, column: 14, scope: !519)
!519 = !DILexicalBlockFile(scope: !520, file: !1, discriminator: 1)
!520 = distinct !DILexicalBlock(scope: !516, file: !1, line: 458, column: 3)
!521 = !DILocation(line: 458, column: 18, scope: !519)
!522 = !DILocation(line: 458, column: 16, scope: !519)
!523 = !DILocation(line: 458, column: 3, scope: !519)
!524 = !DILocation(line: 459, column: 13, scope: !525)
!525 = distinct !DILexicalBlock(scope: !526, file: !1, line: 459, column: 8)
!526 = distinct !DILexicalBlock(scope: !520, file: !1, line: 458, column: 29)
!527 = !DILocation(line: 459, column: 8, scope: !525)
!528 = !DILocation(line: 459, column: 16, scope: !525)
!529 = !DILocation(line: 459, column: 19, scope: !525)
!530 = !DILocation(line: 459, column: 8, scope: !526)
!531 = !DILocation(line: 460, column: 7, scope: !525)
!532 = !DILocation(line: 461, column: 13, scope: !533)
!533 = distinct !DILexicalBlock(scope: !526, file: !1, line: 461, column: 8)
!534 = !DILocation(line: 461, column: 8, scope: !533)
!535 = !DILocation(line: 461, column: 16, scope: !533)
!536 = !DILocation(line: 461, column: 24, scope: !533)
!537 = !DILocation(line: 461, column: 8, scope: !526)
!538 = !DILocation(line: 462, column: 12, scope: !533)
!539 = !DILocation(line: 462, column: 7, scope: !533)
!540 = !DILocation(line: 462, column: 15, scope: !533)
!541 = !DILocation(line: 462, column: 23, scope: !533)
!542 = !DILocation(line: 463, column: 13, scope: !543)
!543 = distinct !DILexicalBlock(scope: !526, file: !1, line: 463, column: 8)
!544 = !DILocation(line: 463, column: 8, scope: !543)
!545 = !DILocation(line: 463, column: 16, scope: !543)
!546 = !DILocation(line: 463, column: 24, scope: !543)
!547 = !DILocation(line: 463, column: 8, scope: !526)
!548 = !DILocation(line: 464, column: 12, scope: !543)
!549 = !DILocation(line: 464, column: 7, scope: !543)
!550 = !DILocation(line: 464, column: 15, scope: !543)
!551 = !DILocation(line: 464, column: 23, scope: !543)
!552 = !DILocation(line: 465, column: 3, scope: !526)
!553 = !DILocation(line: 458, column: 25, scope: !554)
!554 = !DILexicalBlockFile(scope: !520, file: !1, discriminator: 2)
!555 = !DILocation(line: 458, column: 3, scope: !554)
!556 = !DILocation(line: 562, column: 10, scope: !19)
!557 = !DILocation(line: 562, column: 3, scope: !19)
!558 = !DILocation(line: 563, column: 1, scope: !19)
